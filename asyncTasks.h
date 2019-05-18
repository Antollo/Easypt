#ifndef ASYNCTASK_H_
#define ASYNCTASK_H_

#include <iostream>
#include <list>
#include <thread>
#include <future>
#include <atomic>
#include <algorithm>
#include <memory>
#include "nobject.h"
#include "exception.h"
#include "osDependent.h"

class asyncTasks
{
public:
	//To pass static member to dynamic library
	class staticMembers
	{
	public:
        staticMembers() : threads(), current(threads.begin()) {}
        staticMembers(staticMembers&&) = default;
        staticMembers(const staticMembers&) = delete;
		std::atomic<bool> notReadyFlag;
		std::list<std::thread::id> threads; 
		std::list<std::thread::id>::iterator current;
		std::mutex mutex;
	};
	
	template<class T>
	class future
	{
	public:
		future(std::future<T>&& newFuture) : internal(std::move(newFuture)) {}
		future(future&&) = default;
		future(const future&) = delete;
		T get()
		{
			if (!internal.valid())
				throw InvalidValue("Task already consumed");
			T temp;
			asyncTasks::unregisterThisThread();
			try
			{
				temp = internal.get();
				asyncTasks::registerThisThread();
			}
			catch (...)
			{
				asyncTasks::registerThisThread();
				std::rethrow_exception(std::current_exception());
			}
			return temp;
		}
		bool ready()
		{
			return internal.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready;
		}
		bool valid()
		{
			return internal.valid();
		}
		~future()
		{
			asyncTasks::unregisterThisThread();
			try
			{
				if (internal.valid())
					internal.get();
				asyncTasks::registerThisThread();
			}
			catch (std::exception& e)
        	{
				asyncTasks::registerThisThread();
            	errorOut(getExceptionsArray(e));
        	}
			catch (...)
			{
				asyncTasks::registerThisThread();
				errorOut("Fatal error occurred.");
			}
		}
	private:
		std::future<T> internal;
	};
	
	template<class F>
	static auto makeAsyncTask(F f)
	{
		members->notReadyFlag = true;
		std::future<decltype(f())> internal = std::async(std::launch::async, [f] {
			//initializeThread();
			registerThisThread();
			members->notReadyFlag = false;
			waitForThisThread();
			decltype(f()) temp;
			try
			{
				temp = f();
				unregisterThisThread();
			}
			catch (...)
			{
				unregisterThisThread();
				std::rethrow_exception(std::current_exception());
			}
			return temp;
		});
		while (members->notReadyFlag)
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		waitForThisThread();
		return future<decltype(f())>(std::move(internal));
	}

    using sharedStaticMembers = std::shared_ptr<staticMembers>;
	static sharedStaticMembers members;

	static void initialize(const sharedStaticMembers& newMembers)
	{
		members = newMembers;
	}
	static void registerThisThread()
	{
		std::lock_guard<std::mutex> guard(members->mutex);
		members->threads.push_back(std::this_thread::get_id());
		members->current = members->threads.begin();
		#ifdef DEBUG
		std::cout<<"Thread "<<std::this_thread::get_id()<<" registered"<<std::endl;
		#endif
	}
	static int unregisterThisThread()
	{
		std::lock_guard<std::mutex> guard(members->mutex);
		std::list<std::thread::id>::iterator it;
		int ret = 0;
		while ((it = std::find(members->threads.begin(), members->threads.end(), std::this_thread::get_id())) != members->threads.end())
		{
			members->threads.erase(it);
			ret++;
		}
		members->current = members->threads.begin();
		#ifdef DEBUG
		std::cout<<"Thread "<<std::this_thread::get_id()<<" unregistered "<<ret<<" times"<<std::endl;
		#endif
		return ret;
	}
	static void nextThread()
	{
		std::lock_guard<std::mutex> guard(members->mutex);
		#ifdef DEBUG
		std::cout<<"Thread "<<std::this_thread::get_id()<<" switching"<<std::endl;
		#endif
		members->current = std::next(members->current, 1);
		if (members->current == members->threads.end())
			members->current = members->threads.begin();
		#ifdef DEBUG
		std::cout<<"Thread "<<*members->current<<" is next"<<std::endl;
		#endif
	}
	static void waitForThisThread()
	{
		#ifdef DEBUG
		std::cout<<"Thread "<<std::this_thread::get_id()<<" is waiting"<<std::endl;
		#endif
		while (true)
		{
			members->mutex.lock();
			if (*members->current == std::this_thread::get_id())
			{
				members->mutex.unlock();
				break;
			}
			members->mutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		#ifdef DEBUG
		std::cout<<"Thread "<<std::this_thread::get_id()<<" resumed"<<std::endl;
		#endif
	}
    static void switchTask()
    {
        nextThread();
	    waitForThisThread();
    }
};

#endif
