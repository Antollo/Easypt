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

bool isTrue()
{
    return true;
}

bool isTrue(bool first)
{
    return first;
}
