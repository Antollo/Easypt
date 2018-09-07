#include "nobject.h"

//#define DEBUG

int object::objectCounter = 0;
object::objectPtr object::moveOperator;
object::objectPtr object::Root;

object::object(std::any newValue, name newName)
    :value(newValue), myName(newName), parent(nullptr), pointerToPointerToMeFromWhichIWasAccessed(nullptr)
{
#if defined(DEBUG)
    std::cout<<" CREATE "<<getFullNameString()<<std::endl;
#endif
    objectCounter++;
    if (value.type().hash_code() == typeid(nativeFunctionType).hash_code())
    {
        addSignature("NativeCallable");
        addSignature("Callable");
    }
}

object::objectPtr object::READ(name objectName, bool searchInParent, bool forceCreate)
{
#if defined(DEBUG)
    std::cout<<" READ "<<(std::string)objectName + std::string(" in ") + getFullNameString()<<std::endl;
#endif
    try
    {
        if (children.count(objectName))
            return children[objectName];
        if (forceCreate)
        {
            object::objectPtr newChild = READ(name("Object"), true)->CALL();
            newChild->getName() = objectName;
            addChild(newChild);
            return newChild;
        }
        if (searchInParent && parent != nullptr)
            return parent->READ(objectName, true);
        if (searchInParent)
        {
            if (!hasChild(name("Root")))
                return Root->READ(objectName);
        }
        throw(exception("Cannot find ", objectName, " in ", getFullNameString()));
        return std::make_shared<object>();
    }
    catch(exception& e)
    {
        throw(exception("Error at: ", getFullNameString(), "\n", e.what()));
    }
}

object::objectPtr object::READCALL(object::objectPtr arg)
{
#if defined(DEBUG)
    std::cout<<" READCALL "<<arg->getFullNameString() + std::string(" in ") + getFullNameString()<<std::endl;
#endif
    try
    {
        if (children.count(name("readOperator")))
            return children[name("readOperator")]->CALL(arg);
        throw(exception("Object ", getFullNameString(), " has no readOperator"));
    }
    catch(exception& e)
    {
        throw(exception("Error at: ", getFullNameString(), "\n", e.what()));
    }
}

object::objectPtr object::CALL(object::argsContainer& args)
{
#if defined(DEBUG)
    std::cout << " CALL in " << getFullNameString() << std::endl;
#endif
    try
    {
        if (hasSignature("NativeCallable"))
        {
            nativeFunctionType f = std::any_cast<nativeFunctionType>(value);
            return f(shared_from_this(), args);
        }
        if (children.count(name("callOperator")))
            return children[name("callOperator")]->CALL(args);
        exception e = exception(std::string("Object ") + getFullNameString() + std::string(" is neither Callable nor NativeCallable."));
        throw(e);
        throw(exception("Object ", getFullNameString(), " has no readOperator"));
        return std::make_shared<object>();
    }
    catch(exception& e)
    {
        throw(exception("Error at: ", getFullNameString(), "\n", e.what()));
    }
}

object::objectPtr object::CALL(object::objectPtr arg)
{
    object::argsContainer args(1, arg);
    return CALL(args);
}

object::objectPtr object::CALL()
{
    object::argsContainer args;
    return CALL(args);
}

object::~object()
{
#if defined(DEBUG)
    std::cout<<" DESTROY "<<getFullNameString()<<std::endl;
#endif
    //~ Must not use his parent. Parent is already dead!
    for(auto& child : children)
    {
        child.second->setParent(nullptr);
    }
    if(hasChild(name("~")))
        READ(name("~"))->CALL();
}

object::objectPtr object::getParent(bool throwing)
{
    if(throwing && parent == nullptr)
    {
        throw(exception("Object ", getName(), " has no parent, how sad"));
        return nullptr;
    }
    if (parent == nullptr)
        return nullptr;
    return parent->shared_from_this();
}

object::objectPtr object::debugTree(int indentation)
{
    std::string spaces(indentation * 4, ' ');
    IO::console<<spaces<<"Name:       "<<(std::string)myName<<"\n";
    IO::console<<spaces<<"Location:   "<<std::to_string((intptr_t)this)<<"\n";
    IO::console<<spaces<<"Parent:     "<<((parent != nullptr)?(std::string)parent->getName():"")<<"\n";
    if (signatures.size())
    {
        IO::console<<spaces<<"Signatures: ";
        for(auto& signature : signatures)
            IO::console<<(std::string)signature<<" ";
        IO::console<<"\n";
    }
    if (children.size())
    {
        IO::console<<spaces<<"Children:\n";
        IO::console<<spaces<<"{\n";
        for(auto& child : children)
        {
            std::cout<<"<"<<(std::string)child.first<<">\n";
            child.second->debugTree(indentation+1);
        }
        IO::console<<spaces<<"}\n";
    }
    else
        IO::console<<"\n";
    return shared_from_this();
}


object::objectPtr moveOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->getParent(false))
            args[0]->getParent()->removeChild(args[0]->getName());
        args[0]->getName() = obj->getParent()->getName();
        obj->getParent()->getParent()->addChild(args[0]);
    }
    else
    {
        throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
    }
    return obj;
}
