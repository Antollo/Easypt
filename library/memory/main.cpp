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
    void _or(byteWrapper op)
    {
        (*b) |= (*op.b);
    }
    void _and(byteWrapper op)
    {
        (*b) &= (*op.b);
    }
    void _xor(byteWrapper op)
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
    void _not()
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
        ret->addChildToProto(child.second);
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
        ret->addChildToProto(child.second);
    ret->getValue() = (byteView::byteViewIterator)nullptr;
    return ret;
}
object::objectPtr ByteViewIteratorGet (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("ByteWrapper"), true)->CALL();
    ret->getValue() = byteWrapper(std::any_cast<byteView::byteViewIterator>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr ByteViewIteratorDistance (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("ByteViewIterator")))
        {
            object::objectPtr ret = obj->READ(name("Int"), true)->CALL();
            ret->getValue() = (int) std::distance(*std::any_cast<byteView::byteViewIterator>(&obj->getParent()->getValue()), *std::any_cast<byteView::byteViewIterator>(&args[0]->getValue()));
            return ret;
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not ByteViewIterator in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//ByteWrapper
object::objectPtr ByteWrapper (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChildToProto(child.second);
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
            ->addChild(makeObject(method<byteView, byteView::byteViewIterator (byteView::*)(), &byteView::begin, byteView::byteViewIterator>, name("begin")))
            ->addChild(makeObject(method<byteView, byteView::byteViewIterator (byteView::*)(), &byteView::end, byteView::byteViewIterator>, name("end")))
            ->addChild(makeObject(ByteViewReadOperator, name("readOperator")))
            ->addChild(makeObject(method<byteView, int (byteView::*)(), &byteView::size, int>, name("size")))
            ->addChild(makeObject(ByteViewEqualOperator, name("==")))
        );
    obj->READ(name("Root"), true)->addChild(makeObject(ByteViewIterator, name("ByteViewIterator"))
            ->addChild(makeObject(increment<byteView::byteViewIterator>, name("++")))
            ->addChild(makeObject(decrement<byteView::byteViewIterator>, name("--")))
            ->addChild(makeObject(binaryOperator<byteView::byteViewIterator, byteView::byteViewIterator, int, plus>, name("+")))
            ->addChild(makeObject(binaryOperator<byteView::byteViewIterator, byteView::byteViewIterator, int, minus>, name("-")))
            ->addChild(makeObject(ByteViewIteratorGet, name("get")))
            ->addChild(makeObject(ByteViewIteratorDistance, name("distance")))
            ->addChild(makeObject(binaryOperator<bool, byteView::byteViewIterator, std::equal_to>, name("==")))
            ->addChild(makeObject(binaryOperator<bool, byteView::byteViewIterator, std::greater>, name(">")))
            ->addChild(makeObject(binaryOperator<bool, byteView::byteViewIterator, std::less>, name("<")))
            ->addChild(makeObject(binaryOperator<bool, byteView::byteViewIterator, std::greater_equal>, name(">=")))
            ->addChild(makeObject(binaryOperator<bool, byteView::byteViewIterator, std::less_equal>, name("<=")))
        );
    obj->READ(name("Root"), true)->addChild(makeObject(ByteWrapper, name("ByteWrapper"))
            ->addChild(makeObject(method<byteWrapper, int (byteWrapper::*)(), &byteWrapper::toInt, int>, name("toInt")))
            ->addChild(makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::_or, void, byteWrapper>, name("|=")))
            ->addChild(makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::_and, void, byteWrapper>, name("&=")))
            ->addChild(makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::_xor, void, byteWrapper>, name("^=")))
            ->addChild(makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::shl, void, byteWrapper>, name("<<=")))
            ->addChild(makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::shr, void, byteWrapper>, name(">>=")))
            ->addChild(makeObject(method<byteWrapper, void (byteWrapper::*)(), &byteWrapper::_not, void>, name("~=")))
        );
        
    return nullptr;
}
