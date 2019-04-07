#ifndef SEQUENTIALTASK_H_
#define SEQUENTIALTASK_H_

#include <iostream>
#include <list>
#include <thread>
#include <future>
#include <atomic>
#include <algorithm>
#include <memory>
#include "exception.h"


class SequentialTask
{
public:
	//To pass static member to dynamic library
	class StaticMembers
	{
	public:
        StaticMembers() : threads(), current(threads.begin()) {}
        StaticMembers(const StaticMembers&) = delete;
		std::atomic<bool> notReadyFlag;
		std::list<std::thread::id> threads; 
		std::atomic<std::list<std::thread::id>::iterator> current;
	};
	
	template<class T>
	class Future
	{
	public:
		Future(std::future<T>&& newFuture) : future(std::move(newFuture)) {}
		Future(Future&&) = default;
		T get()
		{
			if (!future.valid())
				throw InvalidValue("Future already consumed");
			T temp;
			SequentialTask::unregisterThisThread();
			try
			{
				temp = future.get();
			}
			catch (...)
			{
				SequentialTask::registerThisThread();
				std::rethrow_exception(std::current_exception());
			}
			SequentialTask::registerThisThread();
			return temp;
		}
		bool ready()
		{
			return future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready;
		}
		bool valid()
		{
			return future.valid();
		}
		~Future()
		{
			int priority = SequentialTask::unregisterThisThread();
			try
			{
				if (future.valid())
					future.get();
			}
			catch (...)
			{
				SequentialTask::registerThisThread(priority);
			}
			SequentialTask::registerThisThread(priority);
		}
	private:
		std::future<T> future;
	};
	
	template<class F>
	static auto makeSequentialTask(F f)
	{
		staticMembers->notReadyFlag = true;
		std::future<decltype(f())> future = std::async(std::launch::async, [f] {
			registerThisThread();
			staticMembers->notReadyFlag = false;
			waitForThisThread();
			decltype(f()) temp;
			try
			{
				temp = f();
			}
			catch (...)
			{
				unregisterThisThread();
				std::rethrow_exception(std::current_exception());
			}
			unregisterThisThread();
			return temp;
		});
		while (staticMembers->notReadyFlag)
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		waitForThisThread();
		return Future<decltype(f())>(std::move(future));
	}

    using SharedStaticMembers = std::shared_ptr<StaticMembers>;
	static SharedStaticMembers staticMembers;

	static void initialize(SharedStaticMembers newStaticMembers)
	{
		staticMembers = newStaticMembers;
	}
	static void registerThisThread(int priority = 1)
	{
		while (priority--)
			staticMembers->threads.push_back(std::this_thread::get_id());
		staticMembers->current.store(staticMembers->threads.begin());
		#ifdef DEBUG
		std::cout<<"Thread "<<std::this_thread::get_id()<<" registered"<<std::endl;
		#endif
	}
	static int unregisterThisThread()
	{
		std::list<std::thread::id>::iterator it;
		int ret = 0;
		while ((it = std::find(staticMembers->threads.begin(), staticMembers->threads.end(), std::this_thread::get_id())) != staticMembers->threads.end())
		{
			staticMembers->threads.erase(it);
			ret++;
		}
		staticMembers->current.store(staticMembers->threads.begin());
		#ifdef DEBUG
		std::cout<<"Thread "<<std::this_thread::get_id()<<" unregistered "<<ret<<" times"<<std::endl;
		#endif
		return ret;
	}
	static void nextThread()
	{
		#ifdef DEBUG
		std::cout<<"Thread "<<std::this_thread::get_id()<<" switching"<<std::endl;
		#endif
		staticMembers->current.store(std::next(staticMembers->current.load(), 1));
		if (staticMembers->current.load() == staticMembers->threads.end())
			staticMembers->current.store(staticMembers->threads.begin());

		//Meh
		auto it = std::find(staticMembers->threads.begin(), staticMembers->threads.end(), *staticMembers->current.load());
		if (it == staticMembers->threads.end())
		{
			staticMembers->current.store(staticMembers->threads.begin());
			std::cout<<"Thread error "<<staticMembers->threads.size()<<std::endl;

		}
		#ifdef DEBUG
		std::cout<<"Thread "<<*staticMembers->current.load()<<" is next"<<std::endl;
		#endif
	}
	static void waitForThisThread()
	{
		#ifdef DEBUG
		std::cout<<"Thread "<<std::this_thread::get_id()<<" is waiting"<<std::endl;
		#endif
		while (*staticMembers->current.load() != std::this_thread::get_id())
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
