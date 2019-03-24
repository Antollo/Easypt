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

object::objectPtr object::CALL(object::arrayType& args)
{
#if defined(DEBUG)
    std::cout << " CALL in " << getFullNameString() << std::endl;
#endif
    try
    {
        if (hasSignature("NativeCallable"))
        {
            nativeFunctionType f = std::any_cast<nativeFunctionType>(value);
            if (!f) throw(InvalidValue("Object ", getFullNameString(), " is abstract function."));
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
    object::arrayType args(1, arg);
    return CALL(args);
}

object::objectPtr object::CALL()
{
    object::arrayType args;
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

object::objectPtr object::callWithParent(objectPtr tempParent, object::arrayType& args)
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
    //~ must not use his parent. Parent is already dead!
    //This object is also dead!
    parent = nullptr;
    for (auto& child : children)
        child.second->setParent(nullptr);
    if (hasChild("~~") && Root != nullptr)
    {
        object::objectPtr dtor = READ("~~");
        if (hasChild("getParent"))
            children.erase(children.find("getParent"));
        if (dtor->hasChild("getParent"))
            dtor->children.erase(dtor->children.find("getParent"));
        try
        {
            dtor->CALL();
        }
        catch (exception& e)
        {
            IO::basicOut << e.getMessage();
        }
        catch (std::exception& e)
        {
            IO::basicOut << "Unknown exception: " + std::string(e.what());
        }
        catch (...)
        {
	    	IO::basicOut << "Fatal error occurred.";
        }
    }
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
    IO::console<<spaces<<"Value:      ";
    if (getValue().type().hash_code() == typeid(nativeFunctionType).hash_code())
        IO::basicOut << (std::string)"native function";
    else if (getValue().type().hash_code() == typeid(std::string).hash_code())
        IO::basicOut << *std::any_cast<std::string>(&getValue());
    else if (getValue().type().hash_code() == typeid(int).hash_code())
        IO::basicOut << *std::any_cast<int>(&getValue());
    else if (getValue().type().hash_code() == typeid(bool).hash_code())
        IO::basicOut << *std::any_cast<bool>(&getValue());
    else if (getValue().type().hash_code() == typeid(double).hash_code())
        IO::basicOut << *std::any_cast<double>(&getValue());
    else if (getValue().type().hash_code() == typeid(arrayType).hash_code())
    {
        for (auto& el : (*std::any_cast<arrayType>(&value)))
            IO::console<<(std::string)el->getName()<<" ";
        IO::console<<"\n";
    }
    else if (getValue().type().hash_code() == typeid(signaturesContainer).hash_code())
    {
        for (auto& el : (*std::any_cast<signaturesContainer>(&value)))
            IO::console<<(std::string)el<<" ";
        IO::console<<"\n";
    }
    else if (value.type().hash_code() == typeid(protoType).hash_code())
    {
        for (auto& el : (*std::any_cast<protoType>(&value)))
            IO::console<<(std::string)el.second->getName()<<" ";
        IO::console<<"\n";
    }
    else if (value.type().hash_code() == typeid(std::nullptr_t).hash_code())
        IO::basicOut << (std::string)"object";
    else
        IO::basicOut << (std::string)"unknown";
    
    //Warning - proto
    if (children.size())
    {
        IO::console<<spaces<<"Children:\n";
        IO::console<<spaces<<"{\n";
        for(auto& child : children)
        {
            if (child.second->getName() != child.first)
                IO::console<<spaces<<"    "<<"Nickname:   "<<(std::string)child.first<<"\n";
            child.second->debugTree(indentation+1);
        }
        IO::console<<spaces<<"}\n";
    }
    else
        IO::console<<"\n";
    return shared_from_this();
}