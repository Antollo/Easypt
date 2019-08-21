#include "Array.h"

//Array constructor
object::objectPtr Array0 (object::objectPtr obj, object::arrayType& args)
{
    obj->getParent()->getValue() = object::arrayType();
    return obj->getParent();
}
object::objectPtr Array1 (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            obj->getParent()->getValue() = object::arrayType();
            (*std::any_cast<object::arrayType>(&obj->getParent()->getValue())).resize(std::any_cast<int>(args[0]->getValue()));
            for(object::objectPtr& el : (*std::any_cast<object::arrayType>(&obj->getParent()->getValue())))
                el = object::getRoot()->READ(name("Object"), true)->CALL();
            return obj->getParent();
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not Int in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr Array2 (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 2)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            obj->getParent()->getValue() = object::arrayType();
            (*std::any_cast<object::arrayType>(&obj->getParent()->getValue())).resize(std::any_cast<int>(args[0]->getValue()));
            for(object::objectPtr& el : (*std::any_cast<object::arrayType>(&obj->getParent()->getValue())))
                el = args[1]->copy();
            return obj->getParent();
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not Int in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//Array methods
object::objectPtr ArrayReadOperator (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            int index = std::any_cast<int>(args[0]->getValue());
            if (index >= 0 && index < std::any_cast<object::arrayType>(obj->getParent()->getValue()).size())
            {
                object::objectPtr ret = obj->READ(name("ArrayIterator"), true)->CALL();
                ret->getValue() = (*std::any_cast<object::arrayType>(&obj->getParent()->getValue())).begin() + index;
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
object::objectPtr ArrayPushBack (object::objectPtr obj, object::arrayType& args)
{
    size_t i = (*std::any_cast<object::arrayType>(&obj->getParent()->getValue())).size();
    (*std::any_cast<object::arrayType>(&obj->getParent()->getValue())).resize(i + args.size());
    for (auto& el : args)
        (*std::any_cast<object::arrayType>(&obj->getParent()->getValue()))[i++] = (el);
    return obj->getParent();
}
object::objectPtr ArrayEqualOperator (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        bool comparison = obj->getParent()->getSignatures() == args[0]->getSignatures();
        if (comparison)
        {
            comparison = (*(std::any_cast<object::arrayType>(&args[0]->getValue()))).size() == (*(std::any_cast<object::arrayType>(&obj->getParent()->getValue()))).size();
            if (comparison)
            {
                auto it = (*(std::any_cast<object::arrayType>(&args[0]->getValue()))).begin();
                for (auto& el : (*(std::any_cast<object::arrayType>(&obj->getParent()->getValue()))))
                {
                    comparison = comparison && std::any_cast<bool>((*(it++))->READ(name("=="))->CALL(el)->getValue());
                    if (!comparison) break;
                }
            }
        }
        object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
        ret->getValue() = comparison;
        return ret;
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//!
object::arrayType ArraySubarray(object::arrayType::iterator a, object::arrayType::iterator b)
{
    return object::arrayType(a, b);
}
object::objectPtr ArrayResize(object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            object::arrayType& arr = *std::any_cast<object::arrayType>(&obj->getParent()->getValue());
            size_t newSize = std::any_cast<int>(args[0]->getValue());
            size_t oldSize = arr.size();
            arr.resize(newSize);

            object::objectPtr object = obj->READ(name("Object"), true)->CALL();
            for (size_t i = oldSize; i < newSize; i++)
                arr[i] = object->copy();
            return obj;
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not Int in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//ArrayIterator constructor
object::objectPtr ArrayIterator (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("Iterator"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addPrototypeChild(child.second);
    ret->getValue() = object::arrayType::iterator();
    return ret;
}
//ArrayIterator methods
object::objectPtr ArrayIteratorGet (object::objectPtr obj, object::arrayType& args)
{
    return *(std::any_cast<object::arrayType::iterator>(obj->getParent()->getValue()));
}
object::objectPtr ArrayIteratorDistance (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("ArrayIterator")))
        {
            object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
            ret->getValue() = (int) std::distance(*std::any_cast<object::arrayType::iterator>(&obj->getParent()->getValue()), *std::any_cast<object::arrayType::iterator>(&args[0]->getValue()));
            return ret;
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not ArrayIterator in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr ArrayIteratorReferenceAssignOperator (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        (*(*std::any_cast<object::arrayType::iterator>(&obj->getParent()->getValue()))) = args[0];
        return obj->getParent();

    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
