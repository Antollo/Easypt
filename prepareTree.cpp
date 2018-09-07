#include "prepareTree.h"

std::pair<object::objectPtr, object::objectPtr> prepareTree()
{
    object::objectPtr Root = std::make_shared<object>(nullptr, name("Root"));
    object::initialize(Root);
    object::objectPtr dot = std::make_shared<object>(nullptr, name("."))->addChild(Root);

    Root->addChild(std::make_shared<object>(errorOut, name("errorOut")));
    //Exception handling ready, here the fun starts
    try
    {
        Root->addChild(std::make_shared<object>(Object, name("Object"))
            ->addChild(std::make_shared<object>(assignOperator, name("=")))
            ->addChild(std::make_shared<object>(instanceOf, name("instanceOf")))
            ->addChild(std::make_shared<object>(merge, name("merge")))
            ->addChild(std::make_shared<object>(getParent, name("getParent")))
            ->addChild(std::make_shared<object>(copy, name("copy")))
            ->addChild(std::make_shared<object>(equalSignaturesTypeOperator, name("===")))
            ->addChild(std::make_shared<object>(equalInternalTypeOperator, name("====")))
            ->addChild(std::make_shared<object>(debugTree, name("debugTree")))
        );

        Root->addChild(std::make_shared<object>(Basic, name("Basic"))
            ->addChild(std::make_shared<object>(nullptr, name("toString")))
            ->addChild(std::make_shared<object>(nullptr, name("toInt")))
            ->addChild(std::make_shared<object>(nullptr, name("toDouble")))
            ->addChild(std::make_shared<object>(nullptr, name("toBoolean")))
        );

        Root->addChild(std::make_shared<object>(Iterable, name("Iterable"))
            ->addChild(std::make_shared<object>(nullptr, name("begin")))
            ->addChild(std::make_shared<object>(nullptr, name("end")))
        );

        Root->addChild(std::make_shared<object>(Iterator, name("Iterator"))
            ->addChild(std::make_shared<object>(nullptr, name("++")))
            ->addChild(std::make_shared<object>(nullptr, name("--")))
            ->addChild(std::make_shared<object>(nullptr, name("get")))
        );

        Root->addChild(std::make_shared<object>(Container, name("Container"))
            ->addChild(std::make_shared<object>(nullptr, name("readOperator")))
            ->addChild(std::make_shared<object>(nullptr, name("size")))
        );

        Root->addChild(std::make_shared<object>(String, name("String"))
            ->addChild(std::make_shared<object>(StringToString, name("toString")))
            ->addChild(std::make_shared<object>(StringToInt, name("toInt")))
            ->addChild(std::make_shared<object>(StringToDouble, name("toDouble")))
            ->addChild(std::make_shared<object>(StringToBoolean, name("toBoolean")))
            ->addChild(std::make_shared<object>(TMethod<std::string, std::string::iterator (std::string::*)(), &std::string::begin, std::string::iterator, typeNames::StringIterator>, name("begin")))
            ->addChild(std::make_shared<object>(TMethod<std::string, std::string::iterator (std::string::*)(), &std::string::end, std::string::iterator, typeNames::StringIterator>, name("end")))
            ->addChild(std::make_shared<object>(StringReadOperator, name("readOperator")))
            ->addChild(std::make_shared<object>(TMethod<std::string, size_t (std::string::*)() const, &std::string::size, int, typeNames::Int>, name("size")))
            ->addChild(std::make_shared<object>(T2BOperator<std::string, std::equal_to, typeNames::String>, name("==")))
            ->addChild(std::make_shared<object>(T2TOperator<std::string, std::plus, typeNames::String>, name("+")))
        );

        Root->addChild(std::make_shared<object>(StringIterator, name("StringIterator"))
            ->addChild(std::make_shared<object>(VMethod<std::string::iterator, std::string::iterator& (std::string::iterator::*)(void), &std::string::iterator::operator++>, name("++")))
            ->addChild(std::make_shared<object>(VMethod<std::string::iterator, std::string::iterator& (std::string::iterator::*)(void), &std::string::iterator::operator-->, name("--")))
            ->addChild(std::make_shared<object>(StringIteratorGet, name("get")))
            ->addChild(std::make_shared<object>(T2BOperator<std::string::iterator, std::equal_to, typeNames::StringIterator>, name("==")))
            ->addChild(std::make_shared<object>(StringIteratorAssignOperator, name("=")))
        );

        Root->addChild(std::make_shared<object>(Int, name("Int"))
            ->addChild(std::make_shared<object>(IntToString, name("toString")))
            ->addChild(std::make_shared<object>(IntToInt, name("toInt")))
            ->addChild(std::make_shared<object>(IntToDouble, name("toDouble")))
            ->addChild(std::make_shared<object>(IntToBoolean, name("toBoolean")))
            ->addChild(std::make_shared<object>(T2BOperator<int, std::equal_to, typeNames::Int>, name("==")))
            ->addChild(std::make_shared<object>(T2TOperator<int, std::plus, typeNames::Int>, name("+")))
            ->addChild(std::make_shared<object>(T2TOperator<int, std::minus, typeNames::Int>, name("-")))
            ->addChild(std::make_shared<object>(T2TOperator<int, std::multiplies, typeNames::Int>, name("*")))
            ->addChild(std::make_shared<object>(T2TOperator<int, std::divides, typeNames::Int>, name("/")))
            ->addChild(std::make_shared<object>(T2TOperator<int, std::modulus, typeNames::Int>, name("%")))
        );

        Root->addChild(std::make_shared<object>(Boolean, name("Boolean"))
            ->addChild(std::make_shared<object>(BooleanToString, name("toString")))
            ->addChild(std::make_shared<object>(BooleanToInt, name("toInt")))
            ->addChild(std::make_shared<object>(BooleanToDouble, name("toDouble")))
            ->addChild(std::make_shared<object>(BooleanToBoolean, name("toBoolean")))
            ->addChild(std::make_shared<object>(T2BOperator<bool, std::equal_to, typeNames::Boolean>, name("==")))
            ->addChild(std::make_shared<object>(T1TOperator<bool, std::logical_not, typeNames::Boolean>, name("!")))
        );

        Root->addChild(std::make_shared<object>(BlockCallable, name("BlockCallable"))
            ->addChild(std::make_shared<object>(BlockCallableIf, name("if")))
            ->addChild(std::make_shared<object>(nullptr, name("while")))
            ->addChild(std::make_shared<object>(BlockCallableFor, name("for")))
            ->addChild(std::make_shared<object>(BlockCallableCallOperator, name("callOperator")))
            ->addChild(std::make_shared<object>(T2BOperator<std::list<expression>, std::equal_to, typeNames::BlockCallable>, name("==")))
        );

        Root->addChild(std::make_shared<object>(Array, name("Array"))
            ->addChild(std::make_shared<object>(TMethod<std::vector<object::objectPtr>, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(), &std::vector<object::objectPtr>::begin, std::vector<object::objectPtr>::iterator, typeNames::ArrayIterator>, name("begin")))
            ->addChild(std::make_shared<object>(TMethod<std::vector<object::objectPtr>, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(), &std::vector<object::objectPtr>::begin, std::vector<object::objectPtr>::iterator, typeNames::ArrayIterator>, name("end")))
            ->addChild(std::make_shared<object>(ArrayReadOperator, name("readOperator")))
            ->addChild(std::make_shared<object>(TMethod<std::vector<object::objectPtr>, size_t (std::vector<object::objectPtr>::*)() const, &std::vector<object::objectPtr>::size, int, typeNames::Int>, name("size")))
            ->addChild(std::make_shared<object>(T2BOperator< std::vector<object::objectPtr>, std::equal_to, typeNames::Array>, name("==")))
            ->addChild(std::make_shared<object>(ArrayPushBack, name("pushBack")))
        );

        Root->addChild(std::make_shared<object>(ArrayIterator, name("ArrayIterator"))
            ->addChild(std::make_shared<object>(VMethod<std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator& (std::vector<object::objectPtr>::iterator::*)(void), &std::vector<object::objectPtr>::iterator::operator++>, name("++")))
            ->addChild(std::make_shared<object>(VMethod<std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator& (std::vector<object::objectPtr>::iterator::*)(void), &std::vector<object::objectPtr>::iterator::operator-->, name("--")))
            ->addChild(std::make_shared<object>(ArrayIteratorGet, name("get")))
            ->addChild(std::make_shared<object>(T2BOperator<std::vector<object::objectPtr>::iterator, std::equal_to, typeNames::ArrayIterator>, name("==")))
            ->addChild(std::make_shared<object>(ArrayIteratorAssignOperator, name("=")))
        );

        Root->addChild(std::make_shared<object>(parse, name("parse"))
        );

        Root->addChild(Root->READ(name("Array"))->CALL()->setName("launchArgs"));
    }
    catch (exception& e)
    {
        Root->READ(name("errorOut"))->CALL(std::make_shared<object>(std::string(e.what()), name("exception")))->READ(name("instanceOf"));
    }

    return std::make_pair(dot, Root);
}
