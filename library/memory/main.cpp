#include <memory>
#include <cstring>
#include <cstdint>
#include <algorithm>
#include "nobject.h"
#include "Common.h"

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

extern "C"
{
    EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args);
}



extern const char typeNamesByteView[] = "ByteView";
extern const char typeNamesByteViewIterator[] = "ByteViewIterator";
extern const char typeNamesByteWrapper[] = "ByteWrapper";

class byteWrapper
{
public:
    using byte = uint8_t;
    byteWrapper(byte* newB) : b(newB) {}
    int toInt()
    {
        return *b;
    }
    void or(byteWrapper op)
    {
        (*b) |= (*op.b);
    }
    void and(byteWrapper op)
    {
        (*b) &= (*op.b);
    }
    void xor(byteWrapper op)
    {
        (*b) ^= (*op.b);
    }
    void shl(byteWrapper op)
    {
        (*b) = (*b) << (*op.b);
    }
    void shr(byteWrapper op)
    {
        (*b) = (*b) >> (*op.b);
    }
    void not()
    {
        (*b) = ~(*b);
    }
private:
    byte* b;
};

class byteView
{
public:
    using byte = uint8_t;
    using byteViewIterator = byte*;
    template <class T>
    byteView(T* x)
    {
        if (std::is_same<T, std::string>::value)
        {
            _data = (byte*) ((std::string*)x)->data();
            _size = ((std::string*)x)->size();
        }
        else
        {
            _data = (byte*) x;
            _size = sizeof(T);
        }
    }
    byteViewIterator begin()
    {
        return _data;
    }
    byteViewIterator end()
    {
        return _data + _size;
    }
    int size()
    {
        return _size;
    }
    bool operator == (const byteView& another)
    {
        return !std::memcmp(_data, another._data, std::min(_size, another._size));
    }
    std::string fromBase64()
    {
        
    }
private:
    size_t _size;
    byte* _data;
};

//ByteView
object::objectPtr ByteView (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Container"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    if (args.size() == 1)
    {
        if (args[0]->getValue().type().hash_code() == typeid(std::string).hash_code())
            ret->getValue() = byteView(std::any_cast<std::string>(&args[0]->getValue()));
        else if (args[0]->getValue().type().hash_code() == typeid(int).hash_code())
            ret->getValue() = byteView(std::any_cast<int>(&args[0]->getValue()));
        else if (args[0]->getValue().type().hash_code() == typeid(bool).hash_code())
            ret->getValue() = byteView(std::any_cast<bool>(&args[0]->getValue()));
        else if (args[0]->getValue().type().hash_code() == typeid(double).hash_code())
            ret->getValue() = byteView(std::any_cast<double>(&args[0]->getValue()));
        else
            throw(WrongTypeOfArgument("Wrong type of argument in ", obj->getFullNameString()));
        return ret;
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr ByteViewReadOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            int index = std::any_cast<int>(args[0]->getValue());
            if (index >= 0 && index < std::any_cast<byteView>(obj->getParent()->getValue()).size())
            {
                object::objectPtr ret = obj->READ(name("ByteViewIterator"), true)->CALL();
                ret->getValue() = (*std::any_cast<byteView>(&obj->getParent()->getValue())).begin() + index;
                return ret;
            }
            throw(OutOfRange("Out of range while calling ", obj->getFullNameString()));
        }
        throw(WrongTypeOfArgument("Argument is not Int in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr ByteViewEqualOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool comparison = obj->getParent()->getSignatures() == args[0]->getSignatures();
        if (comparison)
        {
            comparison = (*(std::any_cast<byteView>(&args[0]->getValue()))).size() == (*(std::any_cast<byteView>(&obj->getParent()->getValue()))).size();
            if (comparison)
            {
                comparison = (*(std::any_cast<byteView>(&args[0]->getValue()))) == (*(std::any_cast<byteView>(&obj->getParent()->getValue())));
            }
        }
        object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
        ret->getValue() = comparison;
        return ret;
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

//ByteViewIterator
object::objectPtr ByteViewIterator (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Iterator"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = (byteView::byteViewIterator)nullptr;
    return ret;
}
object::objectPtr ByteViewIteratorGet (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("ByteWrapper"), true)->CALL();
    ret->getValue() = byteWrapper(std::any_cast<byteView::byteViewIterator>(obj->getParent()->getValue()));
    return ret;
}

//ByteWrapper
object::objectPtr ByteWrapper (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = byteWrapper(nullptr);
    if (args.size() == 1)
    {
        if (args[0]->getValue().type().hash_code() == typeid(int).hash_code())
            ret->getValue() = byteWrapper((byteWrapper::byte*) std::any_cast<int>(&args[0]->getValue()));
    }
    return ret;
}

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args)
{
    name::initialize(std::any_cast<name::initializationPack>(args[0]->getValue()));
    object::initialize(obj->READ(name("Root"), true));

    obj->READ(name("Root"), true)->addChild(makeObject(ByteView, name("ByteView"))
            ->addChild(makeObject(TMethod<byteView, byteView::byteViewIterator (byteView::*)(), &byteView::begin, byteView::byteViewIterator, typeNamesByteViewIterator>, name("begin")))
            ->addChild(makeObject(TMethod<byteView, byteView::byteViewIterator (byteView::*)(), &byteView::end, byteView::byteViewIterator, typeNamesByteViewIterator>, name("end")))
            ->addChild(makeObject(ByteViewReadOperator, name("readOperator")))
            ->addChild(makeObject(TMethod<byteView, int (byteView::*)(), &byteView::size, int, typeNames::Int>, name("size")))
            ->addChild(makeObject(ByteViewEqualOperator, name("==")))
        );
    obj->READ(name("Root"), true)->addChild(makeObject(ByteViewIterator, name("ByteViewIterator"))
            ->addChild(makeObject(increment<byteView::byteViewIterator>, name("++")))
            ->addChild(makeObject(decrement<byteView::byteViewIterator>, name("--")))
            ->addChild(makeObject(TXTOperator<byteView::byteViewIterator, int, plus, typeNamesByteViewIterator, typeNames::Int>, name("+")))
            ->addChild(makeObject(TXTOperator<byteView::byteViewIterator, int, minus, typeNamesByteViewIterator, typeNames::Int>, name("-")))
            ->addChild(makeObject(ByteViewIteratorGet, name("get")))
            ->addChild(makeObject(T2BOperator<byteView::byteViewIterator, std::equal_to, typeNamesByteViewIterator>, name("==")))
            ->addChild(makeObject(T2BOperator<byteView::byteViewIterator, std::greater, typeNamesByteViewIterator>, name(">")))
            ->addChild(makeObject(T2BOperator<byteView::byteViewIterator, std::less, typeNamesByteViewIterator>, name("<")))
            ->addChild(makeObject(T2BOperator<byteView::byteViewIterator, std::greater_equal, typeNamesByteViewIterator>, name(">=")))
            ->addChild(makeObject(T2BOperator<byteView::byteViewIterator, std::less_equal, typeNamesByteViewIterator>, name("<=")))
        );
    obj->READ(name("Root"), true)->addChild(makeObject(ByteWrapper, name("ByteWrapper"))
            ->addChild(makeObject(TMethod<byteWrapper, int (byteWrapper::*)(), &byteWrapper::toInt, int, typeNames::Int>, name("toInt")))
            ->addChild(makeObject(VMethod<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::or, byteWrapper>, name("|=")))
            ->addChild(makeObject(VMethod<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::and, byteWrapper>, name("&=")))
            ->addChild(makeObject(VMethod<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::xor, byteWrapper>, name("^=")))
            ->addChild(makeObject(VMethod<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::shl, byteWrapper>, name("<<=")))
            ->addChild(makeObject(VMethod<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::shr, byteWrapper>, name(">>=")))
            ->addChild(makeObject(VMethod<byteWrapper, void (byteWrapper::*)(), &byteWrapper::not>, name("~=")))
        );

    return nullptr;
}
