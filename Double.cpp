#include "Double.h"

//Double constructor
object::objectPtr Double (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Basic"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = 0.0;
    return ret;
}
//Double methods
object::objectPtr DoubleToString (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("String"), true)->CALL();
    ret->getValue() = std::to_string(std::any_cast<double>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr DoubleToInt (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
    ret->getValue() = int(std::any_cast<double>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr DoubleToDouble (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Double"), true)->CALL();
    ret->getValue() = obj->getParent()->getValue();
    return ret;
}
object::objectPtr DoubleToBoolean (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
    ret->getValue() = bool(std::any_cast<double>(obj->getParent()->getValue()));
    return ret;
}
