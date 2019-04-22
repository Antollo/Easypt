#include "String_.h"

//String constructor
object::objectPtr String0 (object::objectPtr obj, object::arrayType& args)
{
    obj->getParent()->getValue() = std::string();
    return obj->getParent();
}
object::objectPtr String2 (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 2)
    {
        if (args[0]->hasSignature(name("Int")) && args[1]->hasSignature(name("String")))
        {
            obj->getParent()->getValue() = std::string();
            char character = typeConverter<char>(std::any_cast<std::string>(args[1]->getValue()));
            (*std::any_cast<std::string>(&obj->getParent()->getValue())).resize(std::any_cast<int>(args[0]->getValue()));
            for(auto& el : (*std::any_cast<std::string>(&obj->getParent()->getValue())))
                el = character;
            return obj->getParent();
        }
        else
        {
            throw(WrongTypeOfArgument("Arguments are not Int and String in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//String methods
object::objectPtr StringToString (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("String"), true)->CALL();
    ret->getValue() = obj->getParent()->getValue();
    return ret;
}
object::objectPtr StringToInt (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
    try
    {
        ret->getValue() = std::stoi(std::any_cast<std::string>(obj->getParent()->getValue()));
    }
    catch (std::invalid_argument&)
    {
        throw(InvalidValue("Invalid parent value in ", obj->getFullNameString()));
    }
    catch (std::out_of_range&)
    {
        throw(OutOfRange("Out of range in ", obj->getFullNameString()));
    }
    return ret;
}
object::objectPtr StringToDouble (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("Double"), true)->CALL();
    try
    {
        ret->getValue() = std::stod(std::any_cast<std::string>(obj->getParent()->getValue()));
    }
    catch (std::invalid_argument& )
    {
        throw(InvalidValue("Invalid parent value in ", obj->getFullNameString()));
    }
    catch (std::out_of_range&)
    {
        throw(OutOfRange("Out of range in ", obj->getFullNameString()));
    }
    return ret;
}
object::objectPtr StringToBoolean (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
    try
    {
        ret->getValue() = (bool) std::any_cast<std::string>(obj->getParent()->getValue()).size();
    }
    catch (std::invalid_argument&)
    {
        throw(InvalidValue("Invalid parent value in ", obj->getFullNameString()));
    }
    catch (std::out_of_range&)
    {
        throw(OutOfRange("Out of range in ", obj->getFullNameString()));
    }
    return ret;
}
object::objectPtr StringToAsciiCode (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
    if (std::any_cast<std::string>(&obj->getParent()->getValue())->empty())
        throw(OutOfRange("Out of range in ", obj->getFullNameString()));
    else
        ret->getValue() =  int ((unsigned char) (*std::any_cast<std::string>(&obj->getParent()->getValue()))[0]);
    return ret;
}
object::objectPtr StringReplace (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 2)
    {
        if (args[0]->hasSignature(name("String")) && args[1]->hasSignature(name("String")))
        {
            std::string what = std::any_cast<std::string>(args[0]->getValue());
            std::string withWhat = std::any_cast<std::string>(args[1]->getValue());
            std::string& internal = *std::any_cast<std::string>(&obj->getParent()->getValue());
            size_t pos = internal.find(what);
            if (pos != std::string::npos)
               internal.replace(pos, what.size(), withWhat);
            return obj->getParent();
        }
        throw(WrongTypeOfArgument("Arguments are not Strings in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr StringReplaceAll (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 2)
    {
        if (args[0]->hasSignature(name("String")) && args[1]->hasSignature(name("String")))
        {
            std::string what = std::any_cast<std::string>(args[0]->getValue());
            std::string withWhat = std::any_cast<std::string>(args[1]->getValue());
            std::string& internal = *std::any_cast<std::string>(&obj->getParent()->getValue());
            size_t pos = internal.find(what);
            while(pos != std::string::npos)
            {
                internal.replace(pos, what.size(), withWhat);
                pos += withWhat.size();
                pos = internal.find(what, pos);
            }
            return obj->getParent();
        }
        throw(WrongTypeOfArgument("Arguments are not Strings in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr StringReadOperator (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            size_t index = std::any_cast<int>(args[0]->getValue());
            if (index >= 0 && index < std::any_cast<std::string>(obj->getParent()->getValue()).size())
            {
                object::objectPtr ret = obj->READ(name("StringIterator"), true)->CALL();
                ret->getValue() = (*std::any_cast<std::string>(&obj->getParent()->getValue())).begin() + index;
                return ret;
            }
            throw(OutOfRange("Out of range while calling ", obj->getFullNameString()));
        }
        throw(WrongTypeOfArgument("Argument is not Int in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//StringIterator constructor
object::objectPtr StringIterator (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("Iterator"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addPrototypeChild(child.second);
    ret->getValue() = std::string::iterator();
    return ret;
}
//StringIterator methods
object::objectPtr StringIteratorGet (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("String"), true)->CALL();
    ret->getValue() = std::string(1, *(std::any_cast<std::string::iterator>(obj->getParent()->getValue())));
    return ret;
}
object::objectPtr StringIteratorDistance (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("StringIterator")))
        {
            object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
            ret->getValue() = (int) std::distance(*std::any_cast<std::string::iterator>(&obj->getParent()->getValue()), *std::any_cast<std::string::iterator>(&args[0]->getValue()));
            return ret;
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not StringIterator in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr StringIteratorReferenceAssignOperator (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Basic")))
        {
            (*(*std::any_cast<std::string::iterator>(&obj->getParent()->getValue()))) = std::any_cast<std::string>(args[0]->READ(name("toString"))->CALL()->getValue()).at(0);
            return obj->getParent();
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not Basic in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}