#include "prepareTree.h"

std::pair<object::objectPtr, object::objectPtr> prepareTree()
{
    object::objectPtr Root = std::make_shared<object>(nullptr, name("Root"));
    object::initialize(Root);
    object::objectPtr dot = std::make_shared<object>(nullptr, name("."))->addChild(Root);

    Root->addChild(std::make_shared<object>(Null, name("Null"))
        ->addChild(std::make_shared<object>(instanceOf, name("instanceOf")))
    );
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
            ->addChild(std::make_shared<object>(equalOperator, name("==")))
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
            ->addChild(std::make_shared<object>(StringBegin, name("begin")))
            ->addChild(std::make_shared<object>(StringEnd, name("end")))
            ->addChild(std::make_shared<object>(StringReadOperator, name("readOperator")))
            ->addChild(std::make_shared<object>(StringSize, name("size")))
            ->addChild(std::make_shared<object>(StringEqualOperator, name("==")))
        );

        Root->addChild(std::make_shared<object>(StringIterator, name("StringIterator"))
            ->addChild(std::make_shared<object>(StringIteratorIncrement, name("++")))
            ->addChild(std::make_shared<object>(StringIteratorDecrement, name("--")))
            ->addChild(std::make_shared<object>(StringIteratorGet, name("get")))
            ->addChild(std::make_shared<object>(StringIteratorEqualOperator, name("==")))
            ->addChild(std::make_shared<object>(StringIteratorAssignOperator, name("=")))
        );

        Root->addChild(std::make_shared<object>(Int, name("Int"))
            ->addChild(std::make_shared<object>(IntToString, name("toString")))
            ->addChild(std::make_shared<object>(IntToInt, name("toInt")))
            ->addChild(std::make_shared<object>(IntToDouble, name("toDouble")))
            ->addChild(std::make_shared<object>(IntToBoolean, name("toBoolean")))
            ->addChild(std::make_shared<object>(IntEqualOperator, name("==")))
        );

        Root->addChild(std::make_shared<object>(Boolean, name("Boolean"))
            ->addChild(std::make_shared<object>(BooleanToString, name("toString")))
            ->addChild(std::make_shared<object>(BooleanToInt, name("toInt")))
            ->addChild(std::make_shared<object>(BooleanToDouble, name("toDouble")))
            ->addChild(std::make_shared<object>(BooleanToBoolean, name("toBoolean")))
            ->addChild(std::make_shared<object>(BooleanEqualOperator, name("==")))
            ->addChild(std::make_shared<object>(BooleanNegateOperator, name("!")))
        );

        Root->addChild(std::make_shared<object>(BlockCallable, name("BlockCallable"))
            ->addChild(std::make_shared<object>(BlockCallableIf, name("if")))
            ->addChild(std::make_shared<object>(nullptr, name("while")))
            ->addChild(std::make_shared<object>(BlockCallableFor, name("for")))
            ->addChild(std::make_shared<object>(BlockCallableCallOperator, name("callOperator")))
            ->addChild(std::make_shared<object>(BlockCallableEqualOperator, name("==")))
        );

        Root->addChild(std::make_shared<object>(Array, name("Array"))
            ->addChild(std::make_shared<object>(ArrayBegin, name("begin")))
            ->addChild(std::make_shared<object>(ArrayEnd, name("end")))
            ->addChild(std::make_shared<object>(ArrayReadOperator, name("readOperator")))
            ->addChild(std::make_shared<object>(ArraySize, name("size")))
            ->addChild(std::make_shared<object>(ArrayEqualOperator, name("==")))
            ->addChild(std::make_shared<object>(ArrayPushBack, name("pushBack")))
        );

        Root->addChild(std::make_shared<object>(ArrayIterator, name("ArrayIterator"))
            ->addChild(std::make_shared<object>(ArrayIteratorIncrement, name("++")))
            ->addChild(std::make_shared<object>(ArrayIteratorDecrement, name("--")))
            ->addChild(std::make_shared<object>(ArrayIteratorGet, name("get")))
            ->addChild(std::make_shared<object>(ArrayIteratorEqualOperator, name("==")))
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
