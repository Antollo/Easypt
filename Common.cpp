#include "Common.h"

const char typeNames::Object[] = "Object";
const char typeNames::String[] = "String";
const char typeNames::StringIterator[] = "StringIterator";
const char typeNames::Int[] = "Int";
const char typeNames::Boolean[] = "Boolean";
const char typeNames::Double[] = "Double";
const char typeNames::Array[] = "Array";
const char typeNames::ArrayIterator[] = "ArrayIterator";
const char typeNames::BlockCallable[] = "BlockCallable";

object::objectPtr wrongNumberOfArguments (object::objectPtr obj, object::argsContainer& args)
{
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr apply (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() != 2)
        throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
    if (!args[1]->hasSignature(name("Array")))
        throw(WrongTypeOfArgument("Second argument is not Array in ", obj->getFullNameString()));
    return args[0]->CALL(std::any_cast<std::vector<object::objectPtr>>(args[1]->getValue()));
}

bool isTrue()
{
    return true;
}

bool isTrue(bool first)
{
    return first;
}
