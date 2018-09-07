#include "Boolean.h"

//Boolean constructor
object::objectPtr Boolean (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Basic"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
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
