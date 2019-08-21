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
    object::arrayType _args = object::arrayType(args.begin() + 2, args.end());
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
            const std::string& source = *std::any_cast<std::string>(&args[0]->getValue());
            object::objectPtr ret = obj->READ(name("BlockCallable"), true)->CALL();
            parser par(source.c_str(), source.size() - 1, object::getRoot().get());
            ret->getValue() = par.parse();
            return ret;

        }
        throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//log
object::objectPtr log (object::objectPtr obj, object::arrayType& args)
{
    for(auto& arg : args)
    {
        if (arg->getValue().type().hash_code() == typeid(std::string).hash_code())
            IO::log << *std::any_cast<std::string>(&arg->getValue());
        else if (arg->getValue().type().hash_code() == typeid(int).hash_code())
            IO::log << *std::any_cast<int>(&arg->getValue());
        else if (arg->getValue().type().hash_code() == typeid(bool).hash_code())
            IO::log << *std::any_cast<bool>(&arg->getValue());
        else if (arg->getValue().type().hash_code() == typeid(double).hash_code())
            IO::log << *std::any_cast<double>(&arg->getValue());
        else if (arg->getValue().type().hash_code() == typeid(object::arrayType).hash_code())
        {
            object::arrayType temp(1, nullptr);
            for(auto& el : *std::any_cast<object::arrayType>(&arg->getValue()))
            {
                temp.front() = el;
                log(obj, temp);
            }
        }
    };
    return obj->READ(name("Object"), true)->CALL();
}

object::objectPtr import (object::objectPtr obj, object::arrayType& args)
{
    static std::set<std::string> imported {"console", "system", "time", "docs", "file", "memory", "math", "devices", "nativeInterface", "version" };
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            std::filesystem::path fileName = *std::any_cast<std::string>(&args[0]->getValue());
            std::filesystem::path executablePath = getExecutablePath().parent_path();
            
            if (imported.count(fileName.stem().string()))
                return obj;
                //return obj->READ(name("Root"), true)->READ(fileName.stem().string());
            imported.insert(fileName.stem().string());

            if (fileName.extension().string() == ".ez"
            || std::filesystem::exists(fileName.string() + ".ez")
            || std::filesystem::exists((executablePath/fileName).string() + ".ez"))
            {
                if (fileName.extension().string() != ".ez") fileName += ".ez";
                std::string source;
                std::ifstream sourceFile(fileName.string());
                if (!sourceFile.is_open())
                {
                    sourceFile.open((executablePath/fileName).string());
                    if (!sourceFile.is_open()) 
                        throw(FileNotFound("Library ", fileName.string(), " not found"));
                }
                std::getline(sourceFile, source, (char)EOF);
                sourceFile.close();

                //Prevent ugly ifs in parser
                source = "  " + source;

                object::objectPtr sourceString = obj->READ(name("String"), true)->CALL();
                sourceString->getValue() = source;
                object::objectPtr sourceBlockCallable = obj->READ(name("parse"), true)->CALL(sourceString);
                sourceBlockCallable->setName(fileName.stem().string());
                obj->READ(name("Root"), true)->addChild(sourceBlockCallable);
                sourceBlockCallable->CALL();
                return obj;
            }
            else
                throw(FileNotFound("Library ", fileName.string(), " not found"));
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
