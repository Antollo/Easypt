#include "nobject.h"
#include "Common.h"
#include "Core.h"
#include "nativeLibrary.h" 
#include "jit.h"


EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::arrayType& args)
{
    nativeLibrary::initialize(obj, args);

    obj->READ(name("Root"), true)->addChild(makeClass({
        obj->READ("Object", true),
        makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
            if (args.size() == 1)
            {
                if (args[0]->hasSignature(name("String")))
                {
                    std::string& code = *std::any_cast<std::string>(&args[0]->getValue());
                    obj->getParent()->getValue() = std::make_shared<jit::interface>(code);
                }
                else
                {
                    throw(WrongTypeOfArgument("Arguments is not String in ", obj->getFullNameString()));
                }
            }
            else
                throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
            return obj->getParent();
        }, name("NativeInterface")),
        makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
            if (args.size() != 1)
                throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
            object::arrayType arr = {obj->getParent(), args[0]};
            return obj->READ("NativeFunction", true)->CALL(arr);
        }, name("readOperator"))
    })->setName("NativeInterface"))
    ->addChild(makeClass({
        obj->READ("Object", true),
        makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
            if (args.size() == 2)
            {
                if (args[0]->hasSignature(name("NativeInterface")) && args[1]->hasSignature(name("String")))
                {
                    std::shared_ptr<jit::interface>& f = *std::any_cast<std::shared_ptr<jit::interface>>(&args[0]->getValue());
                    std::string& s = *std::any_cast<std::string>(&args[1]->getValue());
                    obj->getParent()->getValue() = std::make_pair(f, f->get(s));
                }
                else
                {
                    throw(WrongTypeOfArgument("Arguments are not NativeFunction and String in ", obj->getFullNameString()));
                }
            }
            else
                throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
            return obj->getParent();
        }, name("NativeFunction")),
        makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
            std::pair<std::shared_ptr<jit::interface>, jit::interface::functionType>& p = *std::any_cast<std::pair<std::shared_ptr<jit::interface>, jit::interface::functionType>>(&obj->getParent()->getValue());
            return jit::interface::callFunction(p.second, obj, args);
        }, name("callOperator"))
    })->setName("NativeFunction"));
    return nullptr;
}
