#ifdef _WIN32
    #define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <cstdio>
#include <string>
#include "nobject.h"

object::objectPtr write (object::objectPtr obj, object::arrayType& args)
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
        else if (arg->hasSignature(name("Basic")))
            std::cout << *std::any_cast<std::string>(&(arg->READ(name("toString"))->CALL()->getValue()));
        else
            throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    };
    return obj->getParent();
}

object::objectPtr writeLine (object::objectPtr obj, object::arrayType& args)
{
    write(obj, args);
    std::cout << std::endl;
    return obj->getParent();
}

object::objectPtr read (object::objectPtr obj, object::arrayType& args)
{
    std::string buffer;
    asyncTasks::unregisterThisThread();
    std::cin >> buffer;
    asyncTasks::registerThisThread();
    return obj->READ(name("String"), true)->CALL()->setValue(buffer);
}

object::objectPtr readLine (object::objectPtr obj, object::arrayType& args)
{
    std::string buffer;
    asyncTasks::unregisterThisThread();
    std::getline(std::cin, buffer);
    asyncTasks::registerThisThread();
    return obj->READ(name("String"), true)->CALL()->setValue(buffer);
}

object::objectPtr scan (object::objectPtr obj, object::arrayType& args)
{
    std::string buffer;
    for(auto& arg : args)
    {
        asyncTasks::unregisterThisThread();
        std::cin >> buffer;
        asyncTasks::registerThisThread();
        if (arg->hasSignature(name("String")))
            arg->getValue() = buffer;
        else if (arg->hasSignature(name("Int")))
        {
            try
            {
                arg->getValue() = std::stoi(buffer);
            }
            catch (std::invalid_argument&)
            {
                throw(InvalidValue("Invalid input value in ", obj->getFullNameString()));
            }
            catch (std::out_of_range&)
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
            catch (std::invalid_argument&)
            {
                throw(InvalidValue("Invalid input value in ", obj->getFullNameString()));
            }
            catch (std::out_of_range&)
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
            catch (std::invalid_argument&)
            {
                throw(InvalidValue("Invalid input value in ", obj->getFullNameString()));
            }
            catch (std::out_of_range&)
            {
                throw(OutOfRange("Out of range in ", obj->getFullNameString()));
            }
        }
        else
            throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    };
    return obj->getParent();
}

object::objectPtr beep (object::objectPtr obj, object::arrayType& args)
{
    std::cout << '\a';
    return obj->getParent();
}

object::objectPtr controlSequence (object::objectPtr obj, object::arrayType& args)
{
    for(auto& arg : args)
    {
        if (arg->hasSignature(name("String")))
            std::cout << ("\033[" + *std::any_cast<std::string>(&arg->getValue()));
        else
            throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    };
    return obj->getParent();
}

object::objectPtr fWriteInt (object::objectPtr obj, object::arrayType& args)
{
    std::printf("%d", *std::any_cast<int>(&args.at(0)->getValue()));
    return obj->getParent();
}

object::objectPtr fWriteDouble (object::objectPtr obj, object::arrayType& args)
{
    std::printf("%lf", *std::any_cast<double>(&args.at(0)->getValue()));
    return obj->getParent();
}

object::objectPtr fWriteString (object::objectPtr obj, object::arrayType& args)
{
    std::printf("%s", std::any_cast<std::string>(&args.at(0)->getValue())->c_str());
    return obj->getParent();
}

object::objectPtr fScanInt (object::objectPtr obj, object::arrayType& args)
{
    std::scanf("%i", std::any_cast<int>(&args.at(0)->getValue()));
    return obj->getParent();
}

object::objectPtr fScanDouble (object::objectPtr obj, object::arrayType& args)
{
    std::scanf("%lf", std::any_cast<double>(&args.at(0)->getValue()));
    return obj->getParent();
}

object::objectPtr fScanString16 (object::objectPtr obj, object::arrayType& args)
{
    char temp[17];
    scanf("%16s", temp);
    *std::any_cast<std::string>(&args.at(0)->getValue()) = std::string(temp);
    return obj->getParent();
}

object::objectPtr fScanString256 (object::objectPtr obj, object::arrayType& args)
{
    char temp[257];
    scanf("%256s", temp);
    *std::any_cast<std::string>(&args.at(0)->getValue()) = std::string(temp);
    return obj->getParent();
}

object::objectPtr initConsole (object::objectPtr obj, object::arrayType& args)
{
    obj->addChild(makeObject(write, name("write")))
        ->addChild(makeObject(writeLine, name("writeLine")))
        ->addChild(makeObject(read, name("read")))
        ->addChild(makeObject(readLine, name("readLine")))
        ->addChild(makeObject(scan, name("scan")))
        ->addChild(makeObject(beep, name("beep")))
        ->addChild(makeObject(controlSequence, name("controlSequence")))
        ->addChild(constructObject(obj, "Object", nullptr)->setName("f")
            ->addChild(makeObject(fWriteInt, name("writeInt")))
            ->addChild(makeObject(fWriteDouble, name("writeDouble")))
            ->addChild(makeObject(fWriteString, name("writeString")))
            ->addChild(makeObject(fScanInt, name("scanInt")))
            ->addChild(makeObject(fScanDouble, name("scanDouble")))
            ->addChild(makeObject(fScanString16, name("scanString16")))
            ->addChild(makeObject(fScanString256, name("scanString256")))
        );
    return nullptr;
}
