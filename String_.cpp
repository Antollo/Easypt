#include "String_.h"

//String constructor
object::objectPtr String (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Basic"), true)->CALL();
    ret->READ(name("merge"))->CALL(obj->READ(name("Container"), true)->CALL());
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = std::string();
    return ret;
}
//String methods
object::objectPtr StringToString (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("String"), true)->CALL();
    ret->getValue() = obj->getParent()->getValue();
    return ret;
}
object::objectPtr StringToInt (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
    try
    {
        ret->getValue() = std::stoi(std::any_cast<std::string>(obj->getParent()->getValue()));
    }
    catch (std::invalid_argument& e)
    {
        throw(InvalidValue("Invalid parent value in ", obj->getFullNameString()));
    }
    catch (std::out_of_range& e)
    {
        throw(OutOfRange("Out of range in ", obj->getFullNameString()));
    }
    return ret;
}
object::objectPtr StringToDouble (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Double"), true)->CALL();
    try
    {
        ret->getValue() = std::stod(std::any_cast<std::string>(obj->getParent()->getValue()));
    }
    catch (std::invalid_argument& e)
    {
        throw(InvalidValue("Invalid parent value in ", obj->getFullNameString()));
    }
    catch (std::out_of_range& e)
    {
        throw(OutOfRange("Out of range in ", obj->getFullNameString()));
    }
    return ret;
}
object::objectPtr StringToBoolean (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
    try
    {
        ret->getValue() = (bool) std::any_cast<std::string>(obj->getParent()->getValue()).size();
    }
    catch (std::invalid_argument& e)
    {
        throw(InvalidValue("Invalid parent value in ", obj->getFullNameString()));
    }
    catch (std::out_of_range& e)
    {
        throw(OutOfRange("Out of range in ", obj->getFullNameString()));
    }
    return ret;
}
object::objectPtr StringReadOperator (object::objectPtr obj, object::argsContainer& args)
{

    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            int index = std::any_cast<int>(args[0]->getValue());
            if (index >= 0 && index < std::any_cast<std::string>(obj->getParent()->getValue()).size())
            {

                object::objectPtr ret = obj->READ(name("StringIterator"), true)->CALL();
                ret->getValue() = (*std::any_cast<std::string>(&obj->getParent()->getValue())).begin() + index;
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
//StringIterator constructor
object::objectPtr StringIterator (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Iterator"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = std::string::iterator();
    return ret;
}
//StringIterator methods
object::objectPtr StringIteratorGet (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("String"), true)->CALL();
    ret->getValue() = std::string(1, *(std::any_cast<std::string::iterator>(obj->getParent()->getValue())));
    return ret;
}
object::objectPtr StringIteratorAssignOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Basic")))
        {
            (*(*std::any_cast<std::string::iterator>(&obj->getParent()->getValue()))) = std::any_cast<std::string>(args[0]->READ(name("toString"))->CALL()->getValue())[0];
            return obj->getParent();
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not Basic in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}