#include <chrono>
#include <thread>
#include "nobject.h"
#include "Common.h"

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

extern "C"
{
    EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args);
}

class _clock
{
public:
    _clock() : startTime(std::chrono::system_clock::now()) {}
    
    void restart()
    {
        startTime = std::chrono::system_clock::now();
    }
    
    int getElapsedMilliseconds()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count();
    }

private:
    std::chrono::time_point<std::chrono::system_clock> startTime;
};

int secondsSinceEpoch()
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void sleep(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

object::objectPtr Clock (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = _clock();
    return ret;
};

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args)
{
    name::initialize(std::any_cast<name::initializationPack>(args[0]->getValue()));
    object::initialize(obj->READ(name("Root"), true));

    obj->READ(name("Root"), true)->addChild(makeObject(Clock, name("Clock"))
            ->addChild(makeObject(VMethod<_clock, void (_clock::*)(), &_clock::restart>, name("restart")))
            ->addChild(makeObject(TMethod<_clock, int (_clock::*)(), &_clock::getElapsedMilliseconds, int, typeNames::Int>, name("getElapsedMilliseconds")))
        );
    obj->addChild(makeObject(VFunction<void (*)(int), sleep, int>, name("sleep")))
        ->addChild(makeObject(TFunction<int (*)(), secondsSinceEpoch, int, typeNames::Int>, name("secondsSinceEpoch")));
    return nullptr;
}
