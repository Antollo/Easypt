#include "Core.h"

#include "osDependent.h"

//Exception constructor
object::objectPtr Exception (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
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
//Parse
object::objectPtr parse (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            std::string source = std::any_cast<std::string>(args[0]->getValue());
            object::objectPtr ret = obj->READ(name("BlockCallable"), true)->CALL();
            parser par(source.c_str(), source.size() - 1, object::getRoot());
            ret->getValue() = par.parse();
            return ret;

        }
        throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//basicOut
object::objectPtr basicOut (object::objectPtr obj, object::argsContainer& args)
{
    for(auto& arg : args)
    {
        if (arg->getValue().type().hash_code() == typeid(std::string).hash_code())
            IO::basicOut << *std::any_cast<std::string>(&arg->getValue());
        if (arg->getValue().type().hash_code() == typeid(int).hash_code())
            IO::basicOut << *std::any_cast<int>(&arg->getValue());
        if (arg->getValue().type().hash_code() == typeid(bool).hash_code())
            IO::basicOut << *std::any_cast<bool>(&arg->getValue());
        if (arg->getValue().type().hash_code() == typeid(double).hash_code())
            IO::basicOut << *std::any_cast<double>(&arg->getValue());
    };
    return obj->READ(name("Object"), true)->CALL();
}
//import
inline size_t findLastSlash(std::string& str)
{
    return std::min(str.find_last_of('\\'), str.find_last_of('/'));
}
object::objectPtr import (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            std::string fileName = std::any_cast<std::string>(args[0]->getValue());

            if (fileName.find(".ez") == (fileName.size() - 3))
            {
                std::string source;
                std::ifstream sourceFile(fileName.c_str());
                if (!sourceFile.is_open())
                {
                    std::string executablePath = getExecutablePath();
                    sourceFile.open((executablePath.substr(0, findLastSlash(executablePath) + 1) + fileName).c_str());
                    if (!sourceFile.is_open()) 
                        throw(FileNotFound("Library ", fileName, " not found"));
                }
                std::getline(sourceFile, source, (char)EOF);
                sourceFile.close();

                object::objectPtr sourceString = obj->READ(name("String"), true)->CALL();
                sourceString->getValue() = source;
                object::objectPtr sourceBlockCallable = obj->READ(name("parse"), true)->CALL(sourceString);
                sourceBlockCallable->getName() = std::string(fileName.begin() + findLastSlash(fileName) + 1, fileName.begin()  + fileName.find_last_of('.'));
                obj->READ(name("Root"), true)->addChild(sourceBlockCallable);
                return sourceBlockCallable->CALL();
            }
            else
            {
                object::objectPtr nameInitializationPack = obj->READ(name("Object"), true)->CALL()->setName(name("nameInitializationPack"));
                nameInitializationPack->getValue() = name::getInitializationPack();

                object::objectPtr nativeCallable = obj->READ(name("Object"), true)->CALL();
                nativeCallable->getValue() = dynamicLibrary();
                (*std::any_cast<dynamicLibrary>(&nativeCallable->getValue())).loadLibrary(fileName);
                nativeCallable->getName() = std::string(fileName.begin() + findLastSlash(fileName) + 1, fileName.end());
                obj->READ(name("Root"), true)->addChild(nativeCallable);

                object::nativeFunctionType exportFunction = (*std::any_cast<dynamicLibrary>(&nativeCallable->getValue())).getFunction("exportLibrary");

                object::argsContainer args(1, nameInitializationPack);
                exportFunction(nativeCallable, args);

                return nativeCallable;

            }
        }
        throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
