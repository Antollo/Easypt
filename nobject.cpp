#include "nobject.h"

//#define DEBUG

int object::objectCounter = 0;
object::objectRawPtr object::Root = nullptr;
object::objectPtr object::dot;
std::deque<object::objectPtr> object::dynamicLibraries;

object::object(std::any newValue, name newName)
	:value(newValue), myName(newName), parent(nullptr), automatic(false)
{
#if defined(DEBUG)
    std::cout<<"CREATE "<<getFullNameString()<<std::endl;
#endif
    objectCounter++;
    if (value.type().hash_code() == typeid(nativeFunctionType).hash_code())
    {
        addSignature("NativeCallable");
        addSignature("Callable");
    }
}

object::objectPtr object::READ(name objectName, bool searchInParent, bool forceCreate, bool automatic)
{
#if defined(DEBUG)
    std::cout<<" READ "<<(std::string)objectName + std::string(" in ") + getFullNameString()<<std::endl;
#endif
    try
    {
        if (forceCreate)
        {
            object::objectPtr newChild = READ(name("Object"), true)->CALL();
            newChild->getName() = objectName;
			if (automatic) newChild->setAutomatic();
            addChild(newChild);
            return newChild;
        }
        //if (children.count(objectName))
        if (hasChild(objectName))
            return children[objectName];
        if (searchInParent && parent != nullptr)
            return parent->READ(objectName, true);
        if (searchInParent)
        {
            if (!hasChild(name("Root")) && Root != nullptr)
                return Root->READ(objectName, true);
			else if (Root == nullptr)
				throw(NotFound("Root is not found in ", getFullNameString()));
        }
        throw(NotFound("Cannot find ", objectName, " in ", getFullNameString()));
    }
    catch(exception& e)
    {
        throw(exception(e.getSignature(), "Exception at: ", getFullNameString(), "\n", e.getMessage()));
    }
    catch (std::exception& e)
    {
        throw(exception("Exception", "Exception at: ", getFullNameString(), "\n", "Unknown exception: " + std::string(e.what())));
    }
    catch (object::objectPtr& e)
    {
        if (e->getValue().type().hash_code() == typeid(std::string).hash_code())
            e->setValue("Exception at: " + getFullNameString() + "\n" + (*std::any_cast<std::string>(&e->getValue())));
        throw(e);
    }
}

object::objectPtr object::READCALL(object::objectPtr arg)
{
#if defined(DEBUG)
    std::cout<<" READCALL "<<arg->getFullNameString() + std::string(" in ") + getFullNameString()<<std::endl;
#endif
    try
    {
        if (hasChild("readOperator"))
        //if (children.count(name("readOperator")))
            return children[name("readOperator")]->CALL(arg);
        throw(NotFound("Object ", getFullNameString(), " has no readOperator"));
    }
    catch(exception& e)
    {
        throw(exception(e.getSignature(), "Exception at: ", getFullNameString(), "\n", e.getMessage()));
    }
    catch (std::exception& e)
    {
        throw(exception("Exception", "Exception at: ", getFullNameString(), "\n", "Unknown exception: " + std::string(e.what())));
    }
    catch (object::objectPtr& e)
    {
        if (e->getValue().type().hash_code() == typeid(std::string).hash_code())
            e->setValue("Exception at: " + getFullNameString() + "\n" + (*std::any_cast<std::string>(&e->getValue())));
        throw(e);
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
            //if (!f) throw(InvalidValue("Object ", getFullNameString(), " is abstract function."));
            return f(shared_from_this(), args);
        }
        if (hasChild("callOperator"))
        //if (children.count(name("callOperator")))
            return children[name("callOperator")]->CALL(args);
        throw(InvalidValue("Object ", getFullNameString(), " is neither BlockCallable nor NativeCallable."));
    }
    catch(exception& e)
    {
        throw(exception(e.getSignature(), "Exception at: ", getFullNameString(), "\n", e.getMessage()));
    }
    catch (std::exception& e)
    {
        throw(exception("Exception", "Exception at: ", getFullNameString(), "\n", "Unknown exception: " + std::string(e.what())));
    }
    catch (object::objectPtr& e)
    {
        if (e->getValue().type().hash_code() == typeid(std::string).hash_code())
            e->setValue("Exception at: " + getFullNameString() + "\n" + (*std::any_cast<std::string>(&e->getValue())));
        throw(e);
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

object::objectPtr object::callWithParent(objectPtr tempParent)
{
    object* temp = parent;
    parent = tempParent.get();
    object::objectPtr ret = CALL();
    parent = temp;
    return ret;
}

object::objectPtr object::callWithParent(objectPtr tempParent, objectPtr& arg)
{
    object* temp = parent;
    parent = tempParent.get();
    object::objectPtr ret = CALL(arg);
    parent = temp;
    return ret;
}

object::objectPtr object::callWithParent(objectPtr tempParent, argsContainer& args)
{
    object* temp = parent;
    parent = tempParent.get();
    object::objectPtr ret = CALL(args);
    parent = temp;
    return ret;
}

object::~object()
{
#if defined(DEBUG)
    std::cout<<"DESTROY "<<getFullNameString()<<std::endl;
#endif
    //~ Must not use his parent. Parent is already dead!
    if (hasChild(name("~~")) && Root != nullptr)
        READ(name("~~"))->CALL();
    for (auto& child : children)
        child.second->setParent(nullptr);
}

object::objectPtr object::getParent(bool throwing)
{
    if (throwing && parent == nullptr)
    {
        throw(NotFound("Object ", getName(), " has no parent, how sad"));
        return nullptr;
    }
    if (parent == nullptr)
        return nullptr;
    return parent->shared_from_this();
}

object* object::getRawParent(bool throwing)
{
    if (throwing && parent == nullptr)
    {
        throw(NotFound("Object ", getName(), " has no parent, how sad"));
        return nullptr;
    }
    if (parent == nullptr)
        return nullptr;
    return parent;
}

object::objectPtr object::debugTree(int indentation)
{
    std::string spaces(indentation * 4, ' ');
    IO::console<<spaces<<"Name:       "<<(std::string)myName<<"\n";
    //IO::console<<spaces<<"Location:   "<<std::to_string((intptr_t)this)<<"\n";
    IO::console<<spaces<<"Parent:     "<<((parent != nullptr)?(std::string)parent->getName():"")<<"\n";
    if (signatures.size())
    {
        IO::console<<spaces<<"Signatures: ";
        for(auto& signature : signatures)
            IO::console<<(std::string)signature<<" ";
        IO::console<<"\n";
    }
    if (value.type().hash_code() == typeid(protoType).hash_code())
    {
        IO::console<<spaces<<"Internals: ";
        for (auto& el : (*std::any_cast<protoType>(&value)))
            IO::console<<(std::string)el.second->getName()<<" ";
        IO::console<<"\n";

    }
    //Warning - proto
    if (children.size())
    {
        IO::console<<spaces<<"Children:\n";
        IO::console<<spaces<<"{\n";
        for(auto& child : children)
        {
            IO::console<<spaces<<"    "<<"Nickname:   "<<(std::string)child.first<<"\n";
            child.second->debugTree(indentation+1);
        }
        IO::console<<spaces<<"}\n";
    }
    else
        IO::console<<"\n";
    return shared_from_this();
}