#include <iostream>
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

object::objectPtr write (object::objectPtr obj, object::argsContainer& args)
{
    for(auto& arg : args)
    {
        if (arg->hasSignature(name("String")))
            std::cout << *std::any_cast<std::string>(&arg->getValue());
        else if (arg->hasSignature(name("Int")))
            std::cout << *std::any_cast<int>(&arg->getValue());
        else if (arg->hasSignature(name("Boolean")))
            std::cout << *std::any_cast<bool>(&arg->getValue());
        else if (arg->hasSignature(name("Double")))
            std::cout << *std::any_cast<double>(&arg->getValue());
        else
            throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    };
    return obj->getParent();
}

object::objectPtr writeLine (object::objectPtr obj, object::argsContainer& args)
{
    write(obj, args);
    std::cout << std::endl;
    return obj->getParent();
}

object::objectPtr read (object::objectPtr obj, object::argsContainer& args)
{
    std::string buffer;
    std::cin >> buffer;
    return obj->READ(name("String"), true)->CALL()->setValue(buffer);
}

object::objectPtr readLine (object::objectPtr obj, object::argsContainer& args)
{
    std::string buffer;
    std::getline(std::cin, buffer);
    return obj->READ(name("String"), true)->CALL()->setValue(buffer);
}

object::objectPtr scan (object::objectPtr obj, object::argsContainer& args)
{
    std::string buffer;
    for(auto& arg : args)
    {
        std::cin >> buffer;
        if (arg->hasSignature(name("String")))
            arg->getValue() = buffer;
        else if (arg->hasSignature(name("Int")))
        {
            try
            {
                arg->getValue() = std::stoi(buffer);
            }
            catch (std::invalid_argument& e)
            {
                throw(InvalidValue("Invalid input value in ", obj->getFullNameString()));
            }
            catch (std::out_of_range& e)
            {
                throw(OutOfRange("Out of range in ", obj->getFullNameString()));
            }
        }
        else if (arg->hasSignature(name("Boolean")))
        {
            try
            {
                arg->getValue() = (bool) std::stoi(buffer);
            }
            catch (std::invalid_argument& e)
            {
                throw(InvalidValue("Invalid input value in ", obj->getFullNameString()));
            }
            catch (std::out_of_range& e)
            {
                throw(OutOfRange("Out of range in ", obj->getFullNameString()));
            }
        }
        else if (arg->hasSignature(name("Double")))
        {
            try
            {
                arg->getValue() = std::stod(buffer);
            }
            catch (std::invalid_argument& e)
            {
                throw(InvalidValue("Invalid input value in ", obj->getFullNameString()));
            }
            catch (std::out_of_range& e)
            {
                throw(OutOfRange("Out of range in ", obj->getFullNameString()));
            }
        }
        else
            throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    };
    return obj->getParent();
}

object::objectPtr beep (object::objectPtr obj, object::argsContainer& args)
{
    std::cout << '\a';
    return obj->getParent();
}

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args)
{
    std::ios_base::sync_with_stdio(false);
    name::initialize(std::any_cast<name::initializationPack>(args[0]->getValue()));
    object::initialize(obj->READ(name("Root"), true));

    obj->addChild(makeObject(write, name("write")))
        ->addChild(makeObject(writeLine, name("writeLine")))
        ->addChild(makeObject(read, name("read")))
        ->addChild(makeObject(readLine, name("readLine")))
        ->addChild(makeObject(scan, name("scan")))
        ->addChild(makeObject(beep, name("beep")));
    return nullptr;
}
