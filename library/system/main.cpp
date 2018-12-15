#include <cstdlib>
#include "nobject.h"

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

extern "C"
{
    EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args);
}

object::objectPtr callShellCommand (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            std::system(std::any_cast<std::string>(args[0]->getValue()).c_str());
            return obj->getParent();
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

object::objectPtr getEnvironmentVariable (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            char* res = std::getenv(std::any_cast<std::string>(args[0]->getValue()).c_str());
            return constructObject(obj, "String", std::string((res == nullptr) ? "" : res));
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args)
{
    name::initialize(std::any_cast<name::initializationPack>(args[0]->getValue()));
    object::initialize(obj->READ(name("Root"), true));

    std::string osName = "";
    #if defined(_WIN32)
        osName = "windows";
    #elif defined(__linux__)
        osName = "linux";
    #endif

    obj->addChild(makeObject(callShellCommand, name("callShellCommand")))
        ->addChild(makeObject(getEnvironmentVariable, name("getEnvironmentVariable")))
        ->addChild(constructObject(obj, "String", osName)->setName(name("osName")));
    return nullptr;
}
