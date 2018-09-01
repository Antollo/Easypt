#include "Int.h"

//Int constructor
object::objectPtr Int (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Basic"), true)->CALL();
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("toString"))->copy());
    ret->addChild(obj->READ(name("toInt"))->copy());
    ret->addChild(obj->READ(name("toDouble"))->copy());
    ret->addChild(obj->READ(name("toBoolean"))->copy());
    ret->addChild(obj->READ(name("=="))->copy());
    ret->getValue() = 0;
    return ret;
}
//Int methods
object::objectPtr IntToString (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("String"), true)->CALL();
    ret->getValue() = std::to_string(std::any_cast<int>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr IntToInt (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
    ret->getValue() = obj->getParent()->getValue();
    return ret;
}
object::objectPtr IntToDouble (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Double"), true)->CALL();
    ret->getValue() = double(std::any_cast<int>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr IntToBoolean (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
    ret->getValue() = bool(std::any_cast<int>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr IntEqualOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool firstComparison = (obj->getParent()->getSignatures() == args[0]->getSignatures());
        if (firstComparison)
            firstComparison = (std::any_cast<int>(args[0]->getValue()) == std::any_cast<int>(obj->getParent()->getValue()));
        object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
        ret->getValue() = firstComparison;
        return ret;
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
