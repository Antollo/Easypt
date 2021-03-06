#include "nobject.h"

//#define DEBUG

int object::objectCounter = 0;
object::objectRawPtr object::Root = nullptr;
object::objectPtr object::dot;
object::callStackType object::callStack;

object::object(std::any newValue, name newName)
	:value(newValue), myName(newName), parent(nullptr), automatic(false), beingDestructed(false)
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
    objectifyNoReturn();
}

object::objectPtr object::READ(name objectName, bool searchInParent, object::forceCreateMode forceCreate)
{
#if defined(DEBUG)
    std::cout<<" READ "<<(std::string)objectName + std::string(" in ") + getFullNameString()<<std::endl;
#endif
    try
    {
        if (forceCreate != forceCreateMode::none)
        {
            objectPtr newChild = READ(name("Object"), true)->CALL()->setName(objectName);
			if (forceCreate == forceCreateMode::automatic) newChild->setAutomatic();
            if (forceCreate == forceCreateMode::stack)
                callStack.push(newChild);
            else
                addChild(newChild);
            return newChild;
        }

        //if (children.count(objectName))
        if (hasChild(objectName))
            return children[objectName];

        if (searchInParent)
        {
            objectPtr ptr = callStack.get(objectName);
            if (ptr != nullptr)
                return ptr;
        }
        
        if (searchInParent && parent != nullptr)
            return parent->READ(objectName, true);
        if (searchInParent)
        {
            if (!hasChild(name("Root")) && Root != nullptr)
                return Root->READ(objectName, true);
			else if (Root == nullptr)
				throw(NotFound("Root was already destroyed in opinion of ", getFullNameString()));
        }
        throw(NotFound("Cannot find ", objectName, " in ", getFullNameString()));
    }
    catch (std::exception&)
    {
        std::throw_with_nested(ExceptionAt(getFullNameString()));
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
    catch (std::exception&)
    {
        std::throw_with_nested(ExceptionAt(getFullNameString()));
    }
}

object::objectPtr object::CALL(object::arrayType& args)
{
#if defined(DEBUG)
    std::cout << " CALL in " << getFullNameString() << std::endl;
#endif
    try
    {
        asyncTasks::switchTask();
        object::objectPtr ret = nullptr;
        auto key = callStack.call(shared_from_this());
        if (hasSignature("NativeCallable"))
        {
            nativeFunctionType f = std::any_cast<nativeFunctionType>(value);
            if (!f) throw(InvalidValue("Object ", getFullNameString(), " is abstract function."));
            ret = f(shared_from_this(), args);
        }
        if (hasChild("callOperator"))
        //if (children.count(name("callOperator")))
            ret = children[name("callOperator")]->CALL(args);
        callStack.pop(key);
        if (ret) return ret;
        throw(InvalidValue("Object ", getFullNameString(), " is neither BlockCallable nor NativeCallable."));
    }
    catch (std::exception&)
    {
        std::throw_with_nested(ExceptionAt(getFullNameString()));
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
    objectRawPtr temp = parent;
    parent = tempParent.get();
    object::objectPtr ret = CALL();
    parent = temp;
    return ret;
}

object::objectPtr object::callWithParent(objectPtr tempParent, objectPtr& arg)
{
    objectRawPtr temp = parent;
    parent = tempParent.get();
    object::objectPtr ret = CALL(arg);
    parent = temp;
    return ret;
}

object::objectPtr object::callWithParent(objectPtr tempParent, object::arrayType& args)
{
    objectRawPtr temp = parent;
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
    try
    {
        parent = nullptr;
        for (auto& child : children)
            child.second->setParent(nullptr);
    }
    catch(std::exception& e)
    {
        auto arr = getExceptionsArray(e);
        errorOut(arr);
    }
    catch (...)
    {
	    errorOut("Fatal error occurred.");
    }
}

void object::deleter::operator()(objectRawPtr ptr) const
{
    if (ptr->beingDestructed) return;
    if (ptr->hasChild("~~"))
    {
        ptr->beingDestructed = true;
        try
        {
            ptr->READ("~~")->CALL();
        }
        catch (std::exception& e)
        {
            errorOut(getExceptionsArray(e));
        }
        catch (...)
        {
	    	errorOut("Fatal error occurred.");
        }
    }
    delete ptr;
}

object::objectPtr object::getParent(bool throwing) const
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
        IO::log << (std::string)"native function";
    else if (getValue().type().hash_code() == typeid(std::string).hash_code())
        IO::log << *std::any_cast<std::string>(&getValue());
    else if (getValue().type().hash_code() == typeid(int).hash_code())
        IO::log << *std::any_cast<int>(&getValue());
    else if (getValue().type().hash_code() == typeid(bool).hash_code())
        IO::log << *std::any_cast<bool>(&getValue());
    else if (getValue().type().hash_code() == typeid(double).hash_code())
        IO::log << *std::any_cast<double>(&getValue());
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
        IO::log << (std::string)"object";
    else
        IO::log << (std::string)"unknown";
    
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

object::arrayType getExceptionsArray(std::exception& e)
{
    try
    {
        object::arrayType arr;
        getExceptionsArray(e, arr);
        return arr;
    }
    catch(...)
    {
        errorOut("Fatal error occurred.");
        return {};
    }
}

void getExceptionsArray(std::exception& e, object::arrayType& exceptionsArray)
{
    if (dynamic_cast<objectException*>(&e))
    {
        exceptionsArray.push_back(dynamic_cast<objectException*>(&e)->getPtr());
    }
    else if (dynamic_cast<exception*>(&e))
    {
        exceptionsArray.push_back(constructObject(object::getRoot(), dynamic_cast<exception*>(&e)->getSignature(), dynamic_cast<exception*>(&e)->getMessage()));
    }
    else if (dynamic_cast<std::exception*>(&e))
    {
        exceptionsArray.push_back(constructObject(object::getRoot(), "Exception", dynamic_cast<std::exception*>(&e)->what()));
    }
    try
    {
        std::rethrow_if_nested(e);
    }
    catch (std::exception& nested)
    {
        getExceptionsArray(nested, exceptionsArray);
    }
}
