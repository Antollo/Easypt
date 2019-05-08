#include "nobject.h"
#include "Common.h"
#include "Core.h"
#include "nativeLibrary.h" 
#include "jit.h"

object::objectPtr NativeInterfaceCallOperator (object::objectPtr obj, object::arrayType& args)
{
    return (*(*std::any_cast<std::shared_ptr<jit::function>>(&obj->getParent()->getValue())))(obj, args);
}


EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::arrayType& args)
{
    nativeLibrary::initialize(obj, args);

    obj->READ(name("Root"), true)->addChild(makeClass({
        obj->READ("Object", true),
        makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
            if (args.size() == 2)
            {
                if (args[0]->hasSignature(name("String")) && args[1]->hasSignature(name("String")))
                {
                    std::string name = *std::any_cast<std::string>(&args[0]->getValue());
                    std::string code = *std::any_cast<std::string>(&args[1]->getValue());
                    obj->getParent()->getValue() = std::make_shared<jit::function>(name, code);
                }
                else
                {
                    throw(WrongTypeOfArgument("Arguments are not Strings in ", obj->getFullNameString()));
                }
            }
            else
                throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
            return obj->getParent();
        }, name("NativeInterface")),
        makeObject(NativeInterfaceCallOperator, name("callOperator")),
    })->setName("NativeInterface"));
    return nullptr;
}