#ifndef NOBJECT_H
#define NOBJECT_H

//use c++17 any if your compiler support it.
//#include <any>
#include "anyImplementation/any.hpp"
#include "name.h"
#include "IO.h"
#include "exception.h"
#include <vector>
#include <unordered_set>
#include <iostream>
#include <cstdint>
#include <functional>
#include <deque>
#include <cstddef>
#include <utility>

#define makeObject(...) std::shared_ptr<object>(new object{__VA_ARGS__}, object::deleter())
#define constructObject(caller, type, value) caller->READ(name(type), true)->CALL()->setValue(value)

class object : public std::enable_shared_from_this<object>
{
    public:
        using objectPtr = std::shared_ptr<object>;
        using objectRawPtr = object*;
        using arrayType = std::vector<objectPtr>;
        using nativeFunctionType = objectPtr (*)(objectPtr, arrayType&);
        using childrenType = std::map<name, objectPtr>;
        using signaturesContainer = std::unordered_set<name>;
        using protoType = childrenType;


        object(std::any newValue = nullptr, name newName = getAnonymousName());
        object(object&&) = default;
        object& operator = (object&&) = default;	
        object(const object&) = default;
        object& operator = (const object&) = default;	
        ~object();

        struct deleter
        { 
            void operator()(objectRawPtr ptr) const;
        };

        struct fakeDeleter
        { 
            void operator()(objectRawPtr ptr) const {};
        };

        std::shared_ptr<object> shared_from_this()
        {
            if (beingDestructed) return std::shared_ptr<object>(this, fakeDeleter());
            return std::enable_shared_from_this<object>::shared_from_this();
        }

        bool operator ==(const object& x) const
        {
            return myName == x.myName && signatures == x.signatures && children == x.children;
        }
        objectPtr READ(name objectName, bool searchInParent = false, bool forceCreate = false, bool automatic = false);
        objectPtr READCALL(objectPtr arg);
        objectPtr CALL(arrayType& args);
        objectPtr CALL(objectPtr arg);
        objectPtr CALL();
        objectPtr callWithParent(objectPtr tempParent, arrayType& args);
        objectPtr callWithParent(objectPtr tempParent, objectPtr& arg);
        objectPtr callWithParent(objectPtr tempParent);

        bool hasChild(name childName)
        {
            if (children.count("proto") && (*std::any_cast<protoType>(&children["proto"]->getValue())).count(childName))
            {
                auto it = (*std::any_cast<protoType>(&children["proto"]->getValue())).find(childName);
                children[childName] = it->second->copy();
                children[childName]->setParent(this);
                (*std::any_cast<protoType>(&children["proto"]->getValue())).erase(it);
            }
            return children.count(childName);
        }
        objectPtr addChild(objectPtr child)
        {
            hasChild(child->getName());
            children[child->getName()] = child;
            child->setParent(this);
            return shared_from_this();
        }
        objectPtr addChild(name childName, objectPtr child)
        {
            hasChild(childName);
            children[childName] = child;
            child->setParent(this);
            return shared_from_this();
        }
        objectPtr addPrototypeChild(objectPtr child)
        {
            if (!children.count("proto"))
                addChild(makeObject(protoType(), name("proto")));
            (*std::any_cast<protoType>(&children["proto"]->getValue()))[child->getName()] = child;
            return shared_from_this();
        }
        childrenType& getChildren()
        {
            if (children.count("proto"))
            {
                while (!(*std::any_cast<protoType>(&children["proto"]->getValue())).empty())
                {
                    auto it = (*std::any_cast<protoType>(&children["proto"]->getValue())).begin();
                    children[it->first] = it->second->copy();
                    children[it->first]->setParent(this);
                    (*std::any_cast<protoType>(&children["proto"]->getValue())).erase(it);
                }
                removeChild(name("proto"));
            }
            return children;
        }
        childrenType& getLocalChildren() { return children; }
        objectPtr removeChild(name childName) { if (hasChild(childName)) children.erase(children.find(childName)); return shared_from_this(); }
        objectPtr getParent(bool throwing = true) const;
        objectRawPtr getRawParent(bool throwing = true) const;
        void setParent(objectRawPtr newParent) { parent = newParent; }
        objectPtr setParent(objectPtr newParent) { setParent(newParent.get()); return shared_from_this(); }
        const name& getName() const { return myName; } 
        objectPtr setName(name newName) { myName = newName; return shared_from_this(); }
        std::string getFullNameString() { if(parent != nullptr) return parent->getFullNameString() + std::string(".") + (std::string)getName(); return (std::string)getName(); }
        std::any& getValue() { return value; }
        objectPtr setValue(std::any newValue) { value = newValue; return shared_from_this(); }
        void addSignature(name signature) { signatures.insert(signature); }
        objectPtr addSignatureR(name signature) { signatures.insert(signature); return shared_from_this(); }
        bool hasSignature(name signature) { return signatures.count(signature); }
        signaturesContainer& getSignatures() { return signatures; }
        objectPtr copy()
        {
            objectPtr copyOfThis = makeObject(value, myName);
            copyOfThis->signatures = signatures;
            for(auto& child : children)
                copyOfThis->addChild(child.second->copy());
            return copyOfThis;
        }
        objectPtr fixChildren()
        {
            for(auto& child : children)
                addChild(child.second->fixChildren());
            return shared_from_this();
        }
		objectPtr setAutomatic(bool newAutomatic = true) { automatic = newAutomatic; return shared_from_this(); }
		bool getAutomatic() const { return automatic; }
        objectPtr debugTree(int indentation);
        static void initialize(objectPtr newRoot, objectPtr newDot = nullptr)
        {
            Root = newRoot.get();
			dot = newDot;
        }
		static void release() { Root = nullptr; dot.reset(); dynamicLibraries.clear(); }
        static objectRawPtr getRawRoot() { return Root; }
        static name getAnonymousName()
        {
            return name(std::string("Anonymous") + std::to_string(objectCounter++));
        }
        static void pushDynamicLibrary(objectPtr ptr)
        {
            dynamicLibraries.push_back(ptr);
        }
        static constexpr nativeFunctionType abstractFunction = nullptr;
    private:
        static objectRawPtr Root;
        static objectPtr dot;
        static std::deque<objectPtr> dynamicLibraries;
        static int objectCounter;

        std::any value;
        childrenType children;
        objectRawPtr parent;
        name myName;
        signaturesContainer signatures;
		bool automatic;
        bool beingDestructed;
};

class objectException : public std::exception, object::objectPtr
{
public:
    objectException(const object::objectPtr& obj) : object::objectPtr(obj) {}
    objectException(object::objectPtr&& obj) : object::objectPtr(obj) {}
    const char* what() const noexcept override { return "objectException"; }
    object::objectPtr& getPtr()
    {
        return dynamic_cast<object::objectPtr&>(*this);
    }
};

object::arrayType getExceptionsArray(std::exception& e);
void getExceptionsArray(std::exception& e, object::arrayType& exceptionsArray);

template <class T>
inline void errorOut (T arg)
{
    if constexpr (std::is_same_v<std::decay_t<T>, object::objectPtr>)
    {
        if (arg->getValue().type().hash_code() == typeid(std::string).hash_code())
            std::cerr << "\033[31m" << *std::any_cast<std::string>(&arg->getValue()) << "\033[0m" << std::endl;
        else if (arg->getValue().type().hash_code() == typeid(int).hash_code())
            std::cerr << "\033[31m" << *std::any_cast<int>(&arg->getValue()) << "\033[0m" << std::endl;
        else if (arg->getValue().type().hash_code() == typeid(bool).hash_code())
            std::cerr << "\033[31m" << *std::any_cast<bool>(&arg->getValue()) << "\033[0m" << std::endl;
        else if (arg->getValue().type().hash_code() == typeid(double).hash_code())
            std::cerr << "\033[31m" << *std::any_cast<double>(&arg->getValue()) << "\033[0m" << std::endl;
        else if (arg->getValue().type().hash_code() == typeid(object::arrayType).hash_code())
        {
            for(auto& el : *std::any_cast<object::arrayType>(&arg->getValue()))
            {
                errorOut(el);
            }
        }
    }
    else if constexpr (std::is_same_v<std::decay_t<T>, object::arrayType>)
    {
        for(auto& el : arg)
        {
            errorOut(el);
        }
    }
    else
    {
        std::cerr << "\033[31m" << arg << "\033[0m" << std::endl;
    }
}

#include "asyncTasks.h"

#endif
