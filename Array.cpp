#include "Array.h"

//Array constructor
object::objectPtr Array (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Container"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = std::vector<object::objectPtr>();
    return ret;
}
//Array methods
object::objectPtr ArrayReadOperator (object::objectPtr obj, object::argsContainer& args)
{

    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Basic")))
        {
            int index = std::any_cast<int>(args[0]->READ(name("toInt"))->CALL()->getValue());
            if (index >= 0 && index < std::any_cast<std::vector<object::objectPtr>>(obj->getParent()->getValue()).size())
            {

                object::objectPtr ret = obj->READ(name("ArrayIterator"), true)->CALL();
                ret->getValue() = (*std::any_cast<std::vector<object::objectPtr>>(&obj->getParent()->getValue())).begin() + index;
                return ret;
            }
            else
            {
                throw(exception("Out of range while calling ", obj->getFullNameString()));
            }
        }
        else
        {
            throw(exception("Argument is not Basic in ", obj->getFullNameString()));
        }
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr ArrayPushBack (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        (*std::any_cast<std::vector<object::objectPtr>>(&obj->getParent()->getValue())).push_back(args[0]);
        return obj->getParent();
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
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
        if (args[0]->hasSignature(name("Basic")))
        {
            (*(*std::any_cast<std::vector<object::objectPtr>::iterator>(&obj->getParent()->getValue()))) = args[0];
            return obj->getParent();
        }
        else
        {
            throw(exception("Argument is not Basic in ", obj->getFullNameString()));
        }
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
