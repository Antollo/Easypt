#include "Object.h"

//Object constructor
object::objectPtr Object (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = std::make_shared<object>();
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("instanceOf"))->copy());
    ret->addChild(obj->READ(name("merge"))->copy());
    ret->addChild(obj->READ(name("getParent"))->copy());
    ret->addChild(obj->READ(name("copy"))->copy());
    ret->addChild(obj->READ(name("=="))->copy());
    ret->addChild(obj->READ(name("debugTree"))->copy());
    return ret;
}
//Object methods
object::objectPtr merge (object::objectPtr obj, object::argsContainer& args)
{
    for(auto& arg : args)
    {
        obj->getParent()->getSignatures().insert(arg->getSignatures().begin(), arg->getSignatures().end());
        for(auto& child : obj->getParent()->getChildren())
            obj->getParent()->addChild(child.second->copy());
        obj->getParent()->getValue() = arg->getValue();
    };
    return obj->getParent();
}
object::objectPtr copy (object::objectPtr obj, object::argsContainer& args)
{
    return obj->getParent()->copy();
}
object::objectPtr getParent (object::objectPtr obj, object::argsContainer& args)
{
    return obj->getParent()->getParent();
}
object::objectPtr equalOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool firstComparison = ((obj->getParent()->getSignatures() == args[0]->getSignatures()) && (obj->getParent()->getChildren() == args[0]->getChildren()));
        object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
        ret->getValue() = firstComparison;
        return ret;
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr debugTree (object::objectPtr obj, object::argsContainer& args)
{
    if (obj->getParent(false))
        obj->getParent()->debugTree(0);
    else
        obj->debugTree(0);
    return obj;
}
