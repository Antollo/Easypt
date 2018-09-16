#include "Array.h"

//Array constructor
object::objectPtr Array0 (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Container"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = std::vector<object::objectPtr>();
    return ret;
}
object::objectPtr Array1 (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            object::objectPtr ret = Array0(obj, args), object = obj->READ(name("Object"), true)->CALL();
            (*std::any_cast<std::vector<object::objectPtr>>(&ret->getValue())).resize(std::any_cast<int>(args[0]->getValue()));
            for(object::objectPtr& el : (*std::any_cast<std::vector<object::objectPtr>>(&ret->getValue())))
                el = object->copy();
            return ret;
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not Basic in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr Array2 (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 2)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            object::objectPtr ret = Array0(obj, args), object = args[1];
            (*std::any_cast<std::vector<object::objectPtr>>(&ret->getValue())).resize(std::any_cast<int>(args[0]->getValue()));
            for(object::objectPtr& el : (*std::any_cast<std::vector<object::objectPtr>>(&ret->getValue())))
                el = object->copy();
            return ret;
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not Basic in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//Array methods
object::objectPtr ArrayReadOperator (object::objectPtr obj, object::argsContainer& args)
{

    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            int index = std::any_cast<int>(args[0]->getValue());
            if (index >= 0 && index < std::any_cast<std::vector<object::objectPtr>>(obj->getParent()->getValue()).size())
            {

                object::objectPtr ret = obj->READ(name("ArrayIterator"), true)->CALL();
                ret->getValue() = (*std::any_cast<std::vector<object::objectPtr>>(&obj->getParent()->getValue())).begin() + index;
                return ret;
            }
            else
            {
                throw(OutOfRange("Out of range while calling ", obj->getFullNameString()));
            }
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not Int in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr ArrayPushBack (object::objectPtr obj, object::argsContainer& args)
{
    for (auto& el : args)
        (*std::any_cast<std::vector<object::objectPtr>>(&obj->getParent()->getValue())).push_back(el);
    return obj->getParent();
}
//ArrayIterator constructor
object::objectPtr ArrayIterator (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Iterator"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = std::string::iterator();
    return ret;
}
//ArrayIterator methods
object::objectPtr ArrayIteratorGet (object::objectPtr obj, object::argsContainer& args)
{
    return *(std::any_cast<std::vector<object::objectPtr>::iterator>(obj->getParent()->getValue()));
}
object::objectPtr ArrayIteratorAssignOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        (*(*std::any_cast<std::vector<object::objectPtr>::iterator>(&obj->getParent()->getValue()))) = args[0];
        return obj->getParent();

    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
