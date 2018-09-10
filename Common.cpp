#include "Common.h"

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
        throw(exception("Wrong signatures of arguments while calling ", obj->getFullNameString()));
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//errorOut
object::objectPtr errorOut (object::objectPtr obj, object::argsContainer& args)
{
    for(auto& arg : args)
    {
        if (arg->getValue().type().hash_code() == typeid(std::string).hash_code())
            IO::errorOut << std::any_cast<std::string>(arg->getValue());
        if (arg->getValue().type().hash_code() == typeid(int).hash_code())
            IO::errorOut << std::any_cast<int>(arg->getValue());
        if (arg->getValue().type().hash_code() == typeid(bool).hash_code())
            IO::errorOut << std::any_cast<bool>(arg->getValue());
        if (arg->getValue().type().hash_code() == typeid(double).hash_code())
            IO::errorOut << std::any_cast<double>(arg->getValue());
    };
    return obj->READ(name("Object"), true)->CALL();
}

object::objectPtr WrongNumberOfArguments (object::objectPtr obj, object::argsContainer& args)
{
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

const char typeNames::Object[] = "Object";
const char typeNames::String[] = "String";
const char typeNames::StringIterator[] = "StringIterator";
const char typeNames::Int[] = "Int";
const char typeNames::Boolean[] = "Boolean";
const char typeNames::Double[] = "Double";
const char typeNames::Array[] = "Array";
const char typeNames::ArrayIterator[] = "ArrayIterator";
const char typeNames::BlockCallable[] = "BlockCallable";

bool isTrue()
{
    return true;
}

bool isTrue(bool first)
{
    return first;
}
