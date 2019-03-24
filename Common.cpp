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

object::objectPtr wrongNumberOfArguments (object::objectPtr obj, object::arrayType& args)
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

object::objectPtr Class (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = makeObject(constructor);
    ret->addSignature("Class");
    ret->addChild(makeObject(object::arrayType(), "classProto"));
    ret->addChild(makeObject(object::signaturesContainer(), "classSignatures"));
    object::arrayType& classProto = (*std::any_cast<object::arrayType>(&ret->READ("classProto")->getValue()));
    object::signaturesContainer& classSignatures = (*std::any_cast<object::signaturesContainer>(&ret->READ("classSignatures")->getValue()));

    auto it = args.begin();
    while (it != args.end() && (*it)->hasSignature("Class"))
    {
        for (auto& el : (*std::any_cast<object::arrayType>(&(*it)->READ("classProto")->getValue())))
            classProto.push_back(el);
        classSignatures.insert(
            (*std::any_cast<object::signaturesContainer>(&(*it)->READ("classSignatures")->getValue())).begin(),
            (*std::any_cast<object::signaturesContainer>(&(*it)->READ("classSignatures")->getValue())).end());
        classSignatures.insert((*it)->getName());
        it++;
    }
    while (it != args.end())
    {
        classProto.push_back(*it);
        it++;
    }
    return ret;
}
object::objectPtr makeClass (std::initializer_list<object::objectPtr> args)
{
    object::arrayType temp(args);
    return Class(nullptr, temp);
}
object::objectPtr constructor (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = makeObject();
    ret->addSignature(obj->getName());
    for (auto& signature : (*std::any_cast<object::signaturesContainer>(&obj->READ("classSignatures")->getValue())))
        ret->addSignature(signature);
    for (auto& child : (*std::any_cast<object::arrayType>(&obj->READ("classProto")->getValue())))
        ret->addPrototypeChild(child);
    if (ret->hasChild(obj->getName()))
        ret->READ(obj->getName())->CALL(args);
    for (auto& signature : ret->getSignatures())
        ret->removeChild(signature);
    return ret;
}