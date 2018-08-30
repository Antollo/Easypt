#include "Boolean.h"

//TODO implement boolean
//Boolean constructor
object::objectPtr Boolean (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Basic"), true)->CALL();
    ret->addChild(obj->READ(name("toString"))->copy());
    ret->addChild(obj->READ(name("toInt"))->copy());
    ret->addChild(obj->READ(name("toDouble"))->copy());
    ret->addChild(obj->READ(name("toBoolean"))->copy());
    ret->addChild(obj->READ(name("=="))->copy());
    ret->getValue() = false;
    return ret;
}
