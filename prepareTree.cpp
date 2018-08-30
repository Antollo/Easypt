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
        );

        Root->addChild(std::make_shared<object>(Int, name("Int"))
            ->addChild(std::make_shared<object>(IntToString, name("toString")))
            ->addChild(std::make_shared<object>(IntToInt, name("toInt")))
            ->addChild(std::make_shared<object>(IntToDouble, name("toDouble")))
            ->addChild(std::make_shared<object>(IntToBoolean, name("toBoolean")))
            ->addChild(std::make_shared<object>(IntEqualOperator, name("==")))
        );

        Root->addChild(std::make_shared<object>(Boolean, name("Boolean"))
            ->addChild(std::make_shared<object>(nullptr, name("toString")))
            ->addChild(std::make_shared<object>(nullptr, name("toInt")))
            ->addChild(std::make_shared<object>(nullptr, name("toDouble")))
            ->addChild(std::make_shared<object>(nullptr, name("toBoolean")))
            ->addChild(std::make_shared<object>(nullptr, name("==")))
        );

        Root->addChild(std::make_shared<object>(BlockCallable, name("BlockCallable"))
            ->addChild(std::make_shared<object>(BlockCallableIf, name("if")))
            ->addChild(std::make_shared<object>(nullptr, name("while")))
            ->addChild(std::make_shared<object>(BlockCallableFor, name("for")))
            ->addChild(std::make_shared<object>(BlockCallableCallOperator, name("callOperator")))
            ->addChild(std::make_shared<object>(BlockCallableEqualOperator, name("==")))
        );

        Root->addChild(std::make_shared<object>(parse, name("parse"))
        );

        //object::argsType args (0, object::objectPtr());
        //object::objectPtr O = std::make_shared<object>(F, object::objectPtr(), name("Root"));
        //Parser(Root, args);
        // O->CALL(args);
        //Root->READ(name("abc"), true);
    }
    catch (exception& e)
    {
        Root->READ(name("errorOut"))->CALL(std::make_shared<object>(std::string(e.what()), name("exception")))->READ(name("instanceOf"));
    }

    return std::make_pair(dot, Root);
}
