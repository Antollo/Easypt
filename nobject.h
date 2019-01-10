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


#define makeObject(...) std::make_shared<object>(__VA_ARGS__)
#define constructObject(caller, type, value) caller->READ(name(type), true)->CALL()->setValue(value)

class object : public std::enable_shared_from_this<object>
{
    public:
        typedef std::shared_ptr<object> objectPtr;
        typedef std::vector<objectPtr> argsContainer;
        typedef objectPtr (*nativeFunctionType)(objectPtr, argsContainer&);
        typedef std::map<name, objectPtr> childrenType;
        typedef std::unordered_set<name> signaturesContainer;


        object(std::any newValue = nullptr, name newName = name(std::string("Anonymous") + std::to_string(objectCounter)));
        ~object();
        bool operator ==(const object& x) const
        {
            return myName == x.myName && signatures == x.signatures && children == x.children;
        }
        objectPtr READ(name objectName, bool searchInParent = false, bool forceCreate = false);
        objectPtr READCALL(objectPtr arg);
        objectPtr CALL(argsContainer& args);
        objectPtr CALL(objectPtr arg);
        objectPtr CALL();
        template <class... Args>
        objectPtr callWithParent(objectPtr tempParent, Args... x)
        {
            object* temp = parent;
            parent = tempParent.get();
            object::objectPtr ret = CALL(x...);
            parent = temp;
            return ret;
        }
        template <>
        objectPtr callWithParent(objectPtr tempParent, argsContainer& args)
        {
            object* temp = parent;
            parent = tempParent.get();
            object::objectPtr ret = CALL(args);
            parent = temp;
            return ret;
        }
        objectPtr addChild(objectPtr child)
        {
            children[child->getName()] = child;
            child->setParent(this);
            return shared_from_this();
        }
        childrenType& getChildren() { return children; }
        bool hasChild(name childName) { return children.count(childName); }
        objectPtr removeChild(name childName) { children.erase(children.find(childName)); return shared_from_this(); }
        objectPtr getParent(bool throwing = true);
        void setParent(object* newParent) { parent = newParent; }
        objectPtr setParent(objectPtr newParent) { setParent(newParent.get()); return shared_from_this(); }
        name& getName() { return myName; }
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

        objectPtr debugTree(int indentation);
        static void initialize(objectPtr newRoot)
        {
            Root = newRoot;
        }
        static void release() { Root.reset(); }
        static objectPtr getRoot() { return Root; }
        static name getAnonymousName()
        {
            return name(std::string("Anonymous") + std::to_string(objectCounter++));
        }
    private:
        static objectPtr Root;
        static int objectCounter;

        std::any value;
        childrenType children;
        object* parent;
        name myName;
        signaturesContainer signatures;
};


#endif
