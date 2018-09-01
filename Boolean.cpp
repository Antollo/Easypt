#include "Boolean.h"

//Boolean constructor
object::objectPtr Boolean (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Basic"), true)->CALL();
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("toString"))->copy());
    ret->addChild(obj->READ(name("toInt"))->copy());
    ret->addChild(obj->READ(name("toDouble"))->copy());
    ret->addChild(obj->READ(name("toBoolean"))->copy());
    ret->addChild(obj->READ(name("=="))->copy());
    ret->addChild(obj->READ(name("!"))->copy());
    ret->getValue() = false;
    return ret;
}
//Boolean methods
object::objectPtr BooleanToString (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("String"), true)->CALL();
    ret->getValue() = std::to_string(std::any_cast<bool>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr BooleanToInt (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
    ret->getValue() = int(std::any_cast<bool>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr BooleanToDouble (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Double"), true)->CALL();
    ret->getValue() = double(std::any_cast<bool>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr BooleanToBoolean (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
    ret->getValue() = obj->getParent()->getValue();
    return ret;
}
object::objectPtr BooleanEqualOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool firstComparison = (obj->getParent()->getSignatures() == args[0]->getSignatures());
        if (firstComparison)
            firstComparison = (std::any_cast<bool>(args[0]->getValue()) == std::any_cast<bool>(obj->getParent()->getValue()));
        object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
        ret->getValue() = firstComparison;
        return ret;
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr BooleanNegateOperator (object::objectPtr obj, object::argsContainer& args)
{
    obj->getParent()->getValue() = !(std::any_cast<bool>(obj->getParent()->getValue()));
    return obj->getParent();
}
