#include "Object.h"

//Object constructor
object::objectPtr Object (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = std::make_shared<object>();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    return ret;
}
//Object methods
object::objectPtr assignOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        object::objectPtr tempCopy = args[0]->copy();
        tempCopy->getName() = obj->getParent()->getName();
        *(obj->getParent()) = *(args[0]->copy());
        return obj->getParent()->fixChildren();
    }
        //return obj->getParent()->getParent()->getChildren()[obj->getParent()->getName()] = args[0];
    else
    {
        throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
    }
}
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
object::objectPtr instanceOf (object::objectPtr obj, object::argsContainer& args)
{
    bool isInstanceOf = true;
    for(auto& arg : args)
        isInstanceOf = isInstanceOf && obj->hasSignature(arg->getName());
    object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
    ret->getValue() = std::any(isInstanceOf);
    return ret;
}
object::objectPtr equalTypeOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool firstComparison = (obj->getParent()->getSignatures() == args[0]->getSignatures());
        return obj->READ(name("Boolean"), true)->CALL()->setValue(firstComparison);
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr debugTree (object::objectPtr obj, object::argsContainer& args)
{
    if (obj->getParent(false))
        obj->getParent()->debugTree(0);
    else
        obj->debugTree(0);
    return obj->getParent();
}
