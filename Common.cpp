#include "Common.h"

//Parse
object::objectPtr parse (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            std::string source = std::any_cast<std::string>(args[0]->getValue());
            object::objectPtr ret = obj->READ(name("BlockCallable"), true)->CALL();
            parser par(source.c_str(), source.size() - 1, object::getRoot());
            ret->getValue() = par.parse();
            return ret;

        }
        throw(exception("Wrong signatures of arguments while calling ", obj->getFullNameString()));
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//errorOut
object::objectPtr errorOut (object::objectPtr obj, object::argsContainer& args)
{
    for(auto& arg : args)
    {
        if (arg->getValue().type().hash_code() == typeid(std::string).hash_code())
            IO::errorOut << std::any_cast<std::string>(arg->getValue());
        if (arg->getValue().type().hash_code() == typeid(int).hash_code())
            IO::errorOut << std::any_cast<int>(arg->getValue());
        if (arg->getValue().type().hash_code() == typeid(bool).hash_code())
            IO::errorOut << std::any_cast<bool>(arg->getValue());
    };
    return obj->READ(name("Null"), true)->CALL();
}
//Null and Object method instanceOf
object::objectPtr instanceOf (object::objectPtr obj, object::argsContainer& args)
{
    bool isInstanceOf = true;
    for(auto& arg : args)
        isInstanceOf = isInstanceOf && obj->hasSignature(arg->getName());
    object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
    ret->getValue() = std::any(isInstanceOf);
    return ret;
}
//Null constructor
object::objectPtr Null (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = std::make_shared<object>(nullptr, "null");
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("instanceOf"))->copy());
    return ret;
}
