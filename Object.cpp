#include "Object.h"

//Object constructor
object::objectPtr Object (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = makeObject();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addPrototypeChild(child.second);
    return ret;
}
//Object methods
object::objectPtr assignOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        *(obj->getParent()) = *(args[0]->copy()->setName(obj->getParent()->getName())->setParent(obj->getParent()->getParent(false))->setAutomatic(obj->getParent()->getAutomatic()));
        return obj->getParent()->fixChildren();
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr referenceAssignOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        obj->getParent()->getParent()->getChildren()[obj->getParent()->getName()] = args[0];
        return  obj->getParent();
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr inherit (object::objectPtr obj, object::argsContainer& args)
{
    for(auto& arg : args)
    {
        obj->getParent()->getSignatures().insert(arg->getSignatures().begin(), arg->getSignatures().end());
        for(auto& child : arg->getChildren())
            obj->getParent()->addPrototypeChild(child.second);
        obj->getParent()->getValue() = arg->getValue();
    };
    return obj->getParent();
}
object::objectPtr ObjectCopy (object::objectPtr obj, object::argsContainer& args)
{
    return obj->getParent()->copy();
}
object::objectPtr getParent (object::objectPtr obj, object::argsContainer& args)
{
    return obj->getParent()->getParent();
}
object::objectPtr hasParent (object::objectPtr obj, object::argsContainer& args)
{
    return constructObject(obj, "Boolean", (bool) obj->getParent()->getParent(false));
}
object::objectPtr getChild (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            if (obj->getParent()->hasChild(std::any_cast<std::string>(args[0]->getValue())))
                return obj->getParent()->READ(name(std::any_cast<std::string>(args[0]->getValue())));
            throw(NotFound("Not found ", std::any_cast<std::string>(args[0]->getValue()), " in ", obj->getFullNameString()));
        }
        throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr getChildrenArray (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = constructObject(obj, "Array", std::vector<object::objectPtr>(obj->getParent()->getChildren().size()));
    auto it1 = (*std::any_cast<std::vector<object::objectPtr>>(&ret->getValue())).begin();
    auto it2 = obj->getParent()->getChildren().begin();
    while(it2 != obj->getParent()->getChildren().end())
        *(it1++) = (it2++)->second;
    return ret;
}
object::objectPtr hasChild (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            return constructObject(obj, "Boolean", (bool) obj->getParent()->hasChild(name(std::any_cast<std::string>(args[0]->getValue()))));
        }
        throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr removeChild (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            obj->getParent()->removeChild(name(std::any_cast<std::string>(args[0]->getValue())));
            return  obj->getParent();
        }
        throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr addChild2 (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 2)
    {
        if (args[0]->hasSignature(name("String")))
        {
            obj->getParent()->getChildren()[std::any_cast<std::string>(args[0]->getValue())] = args[1];
            return  obj->getParent();
        }
        throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr addChild1 (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        obj->getParent()->getChildren()[args[0]->getName()] = args[0];
        return  obj->getParent();
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr getName (object::objectPtr obj, object::argsContainer& args)
{
    return constructObject(obj, "String", (std::string) obj->getParent()->getName());
}
object::objectPtr notEqualOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        return obj->getParent()->READ(name("=="))->CALL(args[0])->READ(name("!"))->CALL();
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr equalReferenceOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool comparison = (obj->getParent() == args[0]);
        return obj->READ(name("Boolean"), true)->CALL()->setValue(comparison);
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr equalSignaturesTypeOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool comparison = (obj->getParent()->getSignatures() == args[0]->getSignatures());
        return obj->READ(name("Boolean"), true)->CALL()->setValue(comparison);
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr equalInternalTypeOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool comparison = (obj->getParent()->getValue().type().hash_code() == args[0]->getValue().type().hash_code());
        return obj->READ(name("Boolean"), true)->CALL()->setValue(comparison);
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr debugTree (object::objectPtr obj, object::argsContainer& args)
{
    if (obj->getParent(false))
        obj->getParent()->debugTree(0);
    else
        obj->debugTree(0);
    return obj->getParent();
}
