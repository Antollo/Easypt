#ifdef _WIN32
    #define _CRT_SECURE_NO_WARNINGS
#endif
#include <cstdlib>
#include "nobject.h"
#include "nativeLibrary.h"

object::objectPtr callShellCommand (object::objectPtr obj, object::arrayType& args)
{
    std::string command;
    for (auto& arg : args)
    {
        if (arg->hasSignature(name("String")))
        {
            command += *std::any_cast<std::string>(&args[0]->getValue());
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
        }
    }
    std::system(command.c_str());
    return obj->getParent();
}

object::objectPtr getEnvironmentVariable (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            char* res = std::getenv(std::any_cast<std::string>(&args[0]->getValue())->c_str());
            return constructObject(obj, "String", std::string((res == nullptr) ? "" : res));
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::arrayType& args)
{
    nativeLibrary::initialize(obj, args);

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
