#include "Abstractions.h"

//Basic constructor
object::objectPtr Basic (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("toString"))->copy());
    ret->addChild(obj->READ(name("toInt"))->copy());
    ret->addChild(obj->READ(name("toDouble"))->copy());
    ret->addChild(obj->READ(name("toBoolean"))->copy());
    return ret;
};
//Iterable constructor
object::objectPtr Iterable (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("begin"))->copy());
    ret->addChild(obj->READ(name("end"))->copy());
    return ret;
};
//Iterator constructor
object::objectPtr Iterator (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("++"))->copy());
    ret->addChild(obj->READ(name("--"))->copy());
    ret->addChild(obj->READ(name("get"))->copy());
    return ret;
};
//Container constructor
object::objectPtr Container (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Iterable"), true)->CALL();
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("readOperator"))->copy());
    ret->addChild(obj->READ(name("size"))->copy());
    return ret;
};
