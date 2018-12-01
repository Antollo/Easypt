#include <memory>
#include <cstring>
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


//Work in progress
template <class... Args>
struct type_list
{
    static constexpr int size = sizeof...(Args);
    template <std::size_t N>
    using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
};

extern const char typeNamesBytes[] = "Bytes";
extern const char typeNamesBytesIterator[] = "BytesIterator";
extern const char typeNamesByte[] = "Byte";

class byteWrapper
{
public:
    using byte = unsigned char;
    byteWrapper(byte* newB) : b(newB) {}
    int _int()
    {
        return *b;
    }
private:
    byte* b;
};

class bytes
{
public:
    using byte = unsigned char;
    using byteIterator = byte*;
    template <class T>
    bytes(T* x)
    {
        _data = (byte*) x;
        _size = sizeof(T);
    }
    template <>
    bytes(std::string* x)
    {
        _data = (byte*) x->data();
        _size = x->size();
    }
    byteIterator begin()
    {
        return _data;
    }
    byteIterator end()
    {
        return _data + _size;
    }
    int size()
    {
        return _size;
    }
    bool operator == (const bytes& another)
    {
        return !std::memcmp(_data, another._data, std::min(_size, another._size));
    }
private:
    size_t _size;
    byte* _data;
};

//Bytes
object::objectPtr Bytes (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Container"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    if (args.size() == 1)
    {
        if (args[0]->getValue().type().hash_code() == typeid(std::string).hash_code())
            ret->getValue() = bytes(std::any_cast<std::string>(&args[0]->getValue()));
        else if (args[0]->getValue().type().hash_code() == typeid(int).hash_code())
            ret->getValue() = bytes(std::any_cast<int>(&args[0]->getValue()));
        else if (args[0]->getValue().type().hash_code() == typeid(bool).hash_code())
            ret->getValue() = bytes(std::any_cast<bool>(&args[0]->getValue()));
        else if (args[0]->getValue().type().hash_code() == typeid(double).hash_code())
            ret->getValue() = bytes(std::any_cast<double>(&args[0]->getValue()));
        else
            throw(WrongTypeOfArgument("Wrong type of argument in ", obj->getFullNameString()));
        return ret;
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr BytesReadOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("Int")))
        {
            int index = std::any_cast<int>(args[0]->getValue());
            if (index >= 0 && index < std::any_cast<bytes>(obj->getParent()->getValue()).size())
            {
                object::objectPtr ret = obj->READ(name("BytesIterator"), true)->CALL();
                ret->getValue() = (*std::any_cast<bytes>(&obj->getParent()->getValue())).begin() + index;
                return ret;
            }
            throw(OutOfRange("Out of range while calling ", obj->getFullNameString()));
        }
        throw(WrongTypeOfArgument("Argument is not Int in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr BytesEqualOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool comparison = obj->getParent()->getSignatures() == args[0]->getSignatures();
        if (comparison)
        {
            comparison = (*(std::any_cast<bytes>(&args[0]->getValue()))).size() == (*(std::any_cast<bytes>(&obj->getParent()->getValue()))).size();
            if (comparison)
            {
                comparison = (*(std::any_cast<bytes>(&args[0]->getValue()))) == (*(std::any_cast<bytes>(&obj->getParent()->getValue())));
            }
        }
        object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
        ret->getValue() = comparison;
        return ret;
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

//BytesIterator
object::objectPtr BytesIterator (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Iterator"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = (bytes::byteIterator)nullptr;
    return ret;
}
object::objectPtr BytesIteratorGet (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Byte"), true)->CALL();
    ret->getValue() = byteWrapper(std::any_cast<bytes::byteIterator>(obj->getParent()->getValue()));
    return ret;
}

//Byte
object::objectPtr Byte (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = byteWrapper(nullptr);
    return ret;
}

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args)
{
    name::initialize(std::any_cast<name::initializationPack>(args[0]->getValue()));
    object::initialize(obj->READ(name("Root"), true));

    obj->READ(name("Root"), true)->addChild(makeObject(Bytes, name("Bytes"))
            ->addChild(makeObject(TMethod<bytes, bytes::byteIterator (bytes::*)(), &bytes::begin, bytes::byteIterator, typeNamesBytesIterator>, name("begin")))
            ->addChild(makeObject(TMethod<bytes, bytes::byteIterator (bytes::*)(), &bytes::end, bytes::byteIterator, typeNamesBytesIterator>, name("end")))
            ->addChild(makeObject(BytesReadOperator, name("readOperator")))
            ->addChild(makeObject(TMethod<bytes, int (bytes::*)(), &bytes::size, int, typeNames::Int>, name("size")))
            ->addChild(makeObject(BytesEqualOperator, name("==")))
        );
    obj->READ(name("Root"), true)->addChild(makeObject(BytesIterator, name("BytesIterator"))
            ->addChild(makeObject(increment<bytes::byteIterator>, name("++")))
            ->addChild(makeObject(decrement<bytes::byteIterator>, name("--")))
            ->addChild(makeObject(TXTOperator<bytes::byteIterator, int, plus, typeNamesBytesIterator, typeNames::Int>, name("+")))
            ->addChild(makeObject(TXTOperator<bytes::byteIterator, int, minus, typeNamesBytesIterator, typeNames::Int>, name("-")))
            ->addChild(makeObject(BytesIteratorGet, name("get")))
            ->addChild(makeObject(T2BOperator<bytes::byteIterator, std::equal_to, typeNamesBytesIterator>, name("==")))
            ->addChild(makeObject(T2BOperator<bytes::byteIterator, std::greater, typeNamesBytesIterator>, name(">")))
            ->addChild(makeObject(T2BOperator<bytes::byteIterator, std::less, typeNamesBytesIterator>, name("<")))
            ->addChild(makeObject(T2BOperator<bytes::byteIterator, std::greater_equal, typeNamesBytesIterator>, name(">=")))
            ->addChild(makeObject(T2BOperator<bytes::byteIterator, std::less_equal, typeNamesBytesIterator>, name("<=")))
        );
    obj->READ(name("Root"), true)->addChild(makeObject(Byte, name("Byte"))
            ->addChild(makeObject(TMethod<bytes, bytes::byteIterator (bytes::*)(), &bytes::begin, bytes::byteIterator, typeNamesBytesIterator>, name("begin")))
            ->addChild(makeObject(TMethod<byteWrapper, int (byteWrapper::*)(), &byteWrapper::_int, int, typeNames::Int>, name("toInt")))
        );

    return nullptr;
}
