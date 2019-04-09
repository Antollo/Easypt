#include "Core.h"

#include "osDependent.h"


object::objectPtr apply (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() != 3)
        throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
    if (!args[2]->hasSignature(name("Array")))
        throw(WrongTypeOfArgument("Third argument is not Array in ", obj->getFullNameString()));
    object::arrayType _args = std::any_cast<object::arrayType>(args[2]->getValue());
    return args[1]->callWithParent(args[0], _args);
}
object::objectPtr call (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() < 2)
        throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
    object::arrayType _args = object::arrayType(args.begin() + 1, args.end());
    return args[1]->callWithParent(args[0], _args);
}
//Exception constructor
object::objectPtr Exception (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("String"), true)->CALL();
    ret->addSignature(obj->getName());
    ret->getValue() = (std::string) obj->getName() + ": ";
    for(auto& arg : args)
    {
        if (arg->hasSignature(name("String")))
        {
             (*std::any_cast<std::string>(&ret->getValue())) += (*std::any_cast<std::string>(&arg->getValue()));
        }
        else
            throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    };
    return ret;
}
//except
object::objectPtr except (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() >= 2)
    {
        if (args[0]->hasSignature(name("Boolean")))
        {
            bool boolean = std::any_cast<bool>(args[0]->getValue());
            if (!boolean)
            {
                object::arrayType arr(args.begin() + 2, args.end());
                throw(args[1]->CALL(arr));
            }
            return args[0];
        }
        else if (args[0]->hasSignature(name("Basic")))
        {
            bool boolean = std::any_cast<bool>(args[0]->READ(name("toBoolean"))->CALL()->getValue());
            if (!boolean)
            {
                object::arrayType arr(args.begin() + 2, args.end());
                throw(args[1]->CALL(arr));
            }
            return args[0];
        }
        throw(WrongTypeOfArgument("First argument is not Basic in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//copy
object::objectPtr copy (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        
        return args[0]->copy();
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//Parse
object::objectPtr parse (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            std::string source = std::any_cast<std::string>(args[0]->getValue());
            object::objectPtr ret = obj->READ(name("BlockCallable"), true)->CALL();
            parser par(source.c_str(), source.size() - 1, object::getRawRoot());
            ret->getValue() = par.parse();
            return ret;

        }
        throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//basicOut
object::objectPtr basicOut (object::objectPtr obj, object::arrayType& args)
{
    for(auto& arg : args)
    {
        if (arg->getValue().type().hash_code() == typeid(std::string).hash_code())
            IO::basicOut << *std::any_cast<std::string>(&arg->getValue());
        else if (arg->getValue().type().hash_code() == typeid(int).hash_code())
            IO::basicOut << *std::any_cast<int>(&arg->getValue());
        else if (arg->getValue().type().hash_code() == typeid(bool).hash_code())
            IO::basicOut << *std::any_cast<bool>(&arg->getValue());
        else if (arg->getValue().type().hash_code() == typeid(double).hash_code())
            IO::basicOut << *std::any_cast<double>(&arg->getValue());
        else if (arg->getValue().type().hash_code() == typeid(object::arrayType).hash_code())
        {
            object::arrayType temp(1, nullptr);
            for(auto& el : *std::any_cast<object::arrayType>(&arg->getValue()))
            {
                temp.front() = el;
                basicOut(obj, temp);
            }
        }
    };
    return obj->READ(name("Object"), true)->CALL();
}
//import
inline size_t findLastSlash(std::string& str)
{
    return std::min(str.find_last_of('\\'), str.find_last_of('/'));
}
object::objectPtr import (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            std::string fileName = std::any_cast<std::string>(args[0]->getValue());
            std::string executablePath = getExecutablePath();
            if (fileName.find(".ez") == (fileName.size() - 3)
                || std::ifstream((fileName + ".ez").c_str()).good()
                || std::ifstream((executablePath.substr(0, findLastSlash(executablePath) + 1) + fileName  + ".ez").c_str()).good())
            {
                if (fileName.find(".ez") != (fileName.size() - 3)) fileName += ".ez";
                std::string source;
                std::ifstream sourceFile(fileName.c_str());
                if (!sourceFile.is_open())
                {
                    sourceFile.open((executablePath.substr(0, findLastSlash(executablePath) + 1) + fileName).c_str());
                    if (!sourceFile.is_open()) 
                        throw(FileNotFound("Library ", fileName, " not found"));
                }
                std::getline(sourceFile, source, (char)EOF);
                sourceFile.close();

                //Prevent ugly ifs in parser
                source = "  " + source;

                object::objectPtr sourceString = obj->READ(name("String"), true)->CALL();
                sourceString->getValue() = source;
                object::objectPtr sourceBlockCallable = obj->READ(name("parse"), true)->CALL(sourceString);
                sourceBlockCallable->getName() = std::string(fileName.begin() + findLastSlash(fileName) + 1, fileName.begin()  + fileName.find_last_of('.'));
                obj->READ(name("Root"), true)->addChild(sourceBlockCallable);
                sourceBlockCallable->CALL();
                return sourceBlockCallable;
            }
            else
            {
                object::objectPtr nameInitializationPack = obj->READ(name("Object"), true)->CALL()->setName(name("nameInitializationPack"));
                nameInitializationPack->getValue() = name::getInitializationPack();

                object::objectPtr asyncTasksInitializationPack = obj->READ(name("Object"), true)->CALL()->setName(name("asyncTasksInitializationPack"));
                asyncTasksInitializationPack->getValue() = asyncTasks::members;

                object::objectPtr nativeCallable = obj->READ(name("Object"), true)->CALL();
                nativeCallable->getValue() = dynamicLibrary();
                (*std::any_cast<dynamicLibrary>(&nativeCallable->getValue())).loadLibrary(fileName);
                nativeCallable->getName() = std::string(fileName.begin() + findLastSlash(fileName) + 1, fileName.end());
                obj->READ(name("Root"), true)->addChild(nativeCallable);

                object::nativeFunctionType exportFunction = (*std::any_cast<dynamicLibrary>(&nativeCallable->getValue())).getFunction("exportLibrary");

                object::arrayType args{nameInitializationPack, asyncTasksInitializationPack};
                exportFunction(nativeCallable, args);

				object::pushDynamicLibrary(nativeCallable);

                return nativeCallable;
            }
        }
        throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr instanceOf (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() > 1)
    {
        bool isInstanceOf = true;
        for(auto it = args.begin()+1; it != args.end(); it++)
            isInstanceOf = isInstanceOf && args[0]->hasSignature((*it)->getName());
        return constructObject(obj, "Boolean", isInstanceOf);
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}