#include "Abstractions.h"

//Basic constructor
object::objectPtr Basic (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    //#if defined(DEBUG)
    for (auto& child : obj->getChildren())
        ret->addPrototypeChild(child.second);
    //#endif
    return ret;
};
//Iterable constructor
object::objectPtr Iterable (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    //#if defined(DEBUG)
    for (auto& child : obj->getChildren())
        ret->addPrototypeChild(child.second);
    //#endif
    return ret;
};
//Iterator constructor
object::objectPtr Iterator (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    //#if defined(DEBUG)
    for (auto& child : obj->getChildren())
        ret->addPrototypeChild(child.second);
    //#endif
    return ret;
};
//Container constructor
object::objectPtr Container (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Iterable"), true)->CALL();
    ret->addSignature(obj->getName());
    //#if defined(DEBUG)
    for (auto& child : obj->getChildren())
        ret->addPrototypeChild(child.second);
    //#endif
    return ret;
};
