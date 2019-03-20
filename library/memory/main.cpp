#include <memory>
#include <cstring>
#include <cstdint>
#include <algorithm>
#include "nobject.h"
#include "Common.h"
#include "Core.h"

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

extern "C"
{
    EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::arrayType& args);
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
object::objectPtr ByteView (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->getValue().type().hash_code() == typeid(std::string).hash_code())
            obj->getParent()->getValue() = byteView(std::any_cast<std::string>(&args[0]->getValue()));
        else if (args[0]->getValue().type().hash_code() == typeid(int).hash_code())
            obj->getParent()->getValue() = byteView(std::any_cast<int>(&args[0]->getValue()));
        else if (args[0]->getValue().type().hash_code() == typeid(bool).hash_code())
            obj->getParent()->getValue() = byteView(std::any_cast<bool>(&args[0]->getValue()));
        else if (args[0]->getValue().type().hash_code() == typeid(double).hash_code())
            obj->getParent()->getValue() = byteView(std::any_cast<double>(&args[0]->getValue()));
        else
            throw(WrongTypeOfArgument("Wrong type of argument in ", obj->getFullNameString()));
        return obj->getParent();
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr ByteViewReadOperator (object::objectPtr obj, object::arrayType& args)
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
object::objectPtr ByteViewEqualOperator (object::objectPtr obj, object::arrayType& args)
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
object::objectPtr ByteViewIterator (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("Iterator"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addPrototypeChild(child.second);
    ret->getValue() = (byteView::byteViewIterator)nullptr;
    return ret;
}
object::objectPtr ByteViewIteratorGet (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("ByteWrapper"), true)->CALL();
    ret->getValue() = byteWrapper(std::any_cast<byteView::byteViewIterator>(obj->getParent()->getValue()));
    return ret;
}
object::objectPtr ByteViewIteratorDistance (object::objectPtr obj, object::arrayType& args)
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
object::objectPtr ByteWrapper (object::objectPtr obj, object::arrayType& args)
{
    obj->getParent()->getValue() = byteWrapper(nullptr);
    if (args.size() == 1)
    {
        if (args[0]->getValue().type().hash_code() == typeid(int).hash_code())
            obj->getParent()->getValue() = byteWrapper((byteWrapper::byte*) std::any_cast<int>(&args[0]->getValue()));
    }
    return obj->getParent();
}

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::arrayType& args)
{
    name::initialize(std::any_cast<name::initializationPack>(args[0]->getValue()));
    object::initialize(obj->READ(name("Root"), true));

    obj->READ(name("Root"), true)->addChild(makeClass({
        obj->READ("Iterable", true),
        makeObject(ByteView, name("ByteView")),
        makeObject(method<byteView, byteView::byteViewIterator (byteView::*)(), &byteView::begin, byteView::byteViewIterator>, name("begin")),
        makeObject(method<byteView, byteView::byteViewIterator (byteView::*)(), &byteView::end, byteView::byteViewIterator>, name("end")),
        makeObject(ByteViewReadOperator, name("readOperator")),
        makeObject(method<byteView, int (byteView::*)(), &byteView::size, int>, name("size")),
        makeObject(ByteViewEqualOperator, name("==")),
    })->setName("ByteView"));

    obj->READ(name("Root"), true)->addChild(makeClass({
        obj->READ("Iterator", true),
        makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
            obj->getParent()->getValue() = (byteView::byteViewIterator)nullptr;
            return obj->getParent();
        }, name("ByteViewIterator")),
        makeObject(increment<byteView::byteViewIterator>, name("++")),
        makeObject(decrement<byteView::byteViewIterator>, name("--")),
        makeObject(binaryOperator<byteView::byteViewIterator, byteView::byteViewIterator, int, plus>, name("+")),
        makeObject(binaryOperator<byteView::byteViewIterator, byteView::byteViewIterator, int, minus>, name("-")),
        makeObject(ByteViewIteratorGet, name("get")),
        makeObject(ByteViewIteratorDistance, name("distance")),
        makeObject(binaryOperator<bool, byteView::byteViewIterator, std::equal_to>, name("==")),
        makeObject(binaryOperator<bool, byteView::byteViewIterator, std::greater>, name(">")),
        makeObject(binaryOperator<bool, byteView::byteViewIterator, std::less>, name("<")),
        makeObject(binaryOperator<bool, byteView::byteViewIterator, std::greater_equal>, name(">=")),
        makeObject(binaryOperator<bool, byteView::byteViewIterator, std::less_equal>, name("<=")),
    })->setName("ByteViewIterator"));

    obj->READ(name("Root"), true)->addChild(makeClass({
        obj->READ("Object", true),
        makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
            obj->getParent()->getValue() = byteWrapper(nullptr);
            return obj->getParent();
        }, name("ByteWrapper")),
        makeObject(method<byteWrapper, int (byteWrapper::*)(), &byteWrapper::toInt, int>, name("toInt")),
        makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::_or, void, byteWrapper>, name("|=")),
        makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::_and, void, byteWrapper>, name("&=")),
        makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::_xor, void, byteWrapper>, name("^=")),
        makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::shl, void, byteWrapper>, name("<<=")),
        makeObject(method<byteWrapper, void (byteWrapper::*)(byteWrapper), &byteWrapper::shr, void, byteWrapper>, name(">>=")),
        makeObject(method<byteWrapper, void (byteWrapper::*)(), &byteWrapper::_not, void>, name("~=")),
    })->setName("ByteWrapper"));
        
    return nullptr;
}
