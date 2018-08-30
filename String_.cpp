#include "String_.h"

//String constructor
object::objectPtr String (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Basic"), true)->CALL();
    ret->READ(name("merge"))->CALL(obj->READ(name("Container"), true)->CALL());
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("toString"))->copy());
    ret->addChild(obj->READ(name("toInt"))->copy());
    ret->addChild(obj->READ(name("toDouble"))->copy());
    ret->addChild(obj->READ(name("toBoolean"))->copy());
    ret->addChild(obj->READ(name("begin"))->copy());
    ret->addChild(obj->READ(name("end"))->copy());
    ret->addChild(obj->READ(name("readOperator"))->copy());
    ret->addChild(obj->READ(name("size"))->copy());
    ret->addChild(obj->READ(name("=="))->copy());
    ret->getValue() = std::string();
    return ret;
}
//String methods
object::objectPtr StringToString (object::objectPtr obj, object::argsContainer& args)
{
    return obj->getParent()->copy();
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
        throw(exception("Invalid parent value in ", obj->getFullNameString()));
    }
    catch (std::out_of_range& e)
    {
        throw(exception("Out of range in ", obj->getFullNameString()));
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
        throw(exception("Invalid parent value in ", obj->getFullNameString()));
    }
    catch (std::out_of_range& e)
    {
        throw(exception("Out of range in ", obj->getFullNameString()));
    }
    return ret;
}
object::objectPtr StringToBoolean (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
    try
    {
        ret->getValue() = (bool)std::any_cast<std::string>(obj->getParent()->getValue()).size();
    }
    catch (std::invalid_argument& e)
    {
        throw(exception("Invalid parent value in ", obj->getFullNameString()));
    }
    catch (std::out_of_range& e)
    {
        throw(exception("Out of range in ", obj->getFullNameString()));
    }
    return ret;
}
object::objectPtr StringBegin (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("StringIterator"), true)->CALL();
    ret->getValue() = (*std::any_cast<std::string>(&obj->getParent()->getValue())).begin();
    return ret;
}
object::objectPtr StringEnd (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("StringIterator"), true)->CALL();
    ret->getValue() = (*std::any_cast<std::string>(&obj->getParent()->getValue())).end();
    return ret;
}
object::objectPtr StringReadOperator (object::objectPtr obj, object::argsContainer& args)
{

    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Basic")))
        {
            int index = std::any_cast<int>(args[0]->READ(name("toInt"))->CALL()->getValue());
            if (index >= 0 && index < std::any_cast<std::string>(obj->getParent()->getValue()).size())
            {
                object::objectPtr ret = obj->READ(name("String"), true)->CALL();
                ret->getValue() = std::string(1, std::any_cast<std::string>(obj->getParent()->getValue()).at(index));
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
object::objectPtr StringSize (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
    ret->getValue() = std::any_cast<std::string>(obj->getParent()->getValue()).size();
    return ret;
}
object::objectPtr StringEqualOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool firstComparison = ((obj->getParent()->getSignatures() == args[0]->getSignatures()) && (obj->getParent()->getChildren() == args[0]->getChildren()));
        if (firstComparison)
            firstComparison = (std::any_cast<std::string>(args[0]->getValue()) == std::any_cast<std::string>(obj->getParent()->getValue()));
        object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
        ret->getValue() = firstComparison;
        return ret;
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//StringIterator constructor
object::objectPtr StringIterator (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Iterator"), true)->CALL();
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("++"))->copy());
    ret->addChild(obj->READ(name("--"))->copy());
    ret->addChild(obj->READ(name("get"))->copy());
    ret->addChild(obj->READ(name("=="))->copy());
    ret->getValue() = std::string::iterator();
    return ret;
}
//StringIterator methods
object::objectPtr StringIteratorIncrement (object::objectPtr obj, object::argsContainer& args)
{
    (*std::any_cast<std::string::iterator>(&obj->getParent()->getValue()))++;
    return obj->getParent();
}
object::objectPtr StringIteratorDecrement (object::objectPtr obj, object::argsContainer& args)
{
    (*std::any_cast<std::string::iterator>(&obj->getParent()->getValue()))--;
    return obj->getParent();
}
object::objectPtr StringIteratorGet (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("String"), true)->CALL();
    ret->getValue() = std::string(1, *(std::any_cast<std::string::iterator>(obj->getParent()->getValue())));
    return ret;
}
object::objectPtr StringIteratorEqualOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool firstComparison = ((obj->getParent()->getSignatures() == args[0]->getSignatures()) && (obj->getParent()->getChildren() == args[0]->getChildren()));
        if (firstComparison)
            firstComparison = (std::any_cast<std::string::iterator>(args[0]->getValue()) == std::any_cast<std::string::iterator>(obj->getParent()->getValue()));
        object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
        ret->getValue() = firstComparison;
        return ret;
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
