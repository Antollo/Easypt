#include "prepareTree.h"

void prepareTree()
{
    object::objectPtr Root = makeObject(nullptr, name("Root"));
    object::objectPtr dot = makeObject(nullptr, name("."))->addChild(Root);
	object::initialize(Root, dot);

    Root
        ->addChild(makeObject(apply, name("apply")))
        ->addChild(makeObject(call, name("call")))
        ->addChild(makeObject(basicOut, name("basicOut")))
        ->addChild(makeObject(debugTree, name("debugTree")))
        ->addChild(makeObject(import, name("import")))
        ->addChild(makeObject(instanceOf, name("instanceOf")))
        ->addChild(makeObject(except, name("except")));
    //Exception handling ready, here the fun starts
    try
    {
        Root->addChild(makeObject(Exception, name("Exception")))
            ->addChild(makeObject(Exception, name("WrongTypeOfArgumentException")))
            ->addChild(makeObject(Exception, name("WrongNumberOfArgumentsException")))
            ->addChild(makeObject(Exception, name("FileNotFoundException")))
            ->addChild(makeObject(Exception, name("OutOfRangeException")))
            ->addChild(makeObject(Exception, name("NotSupportedOnThisOSException")))
            ->addChild(makeObject(Exception, name("InvalidValueException")))
            ->addChild(makeObject(Exception, name("ParserException")))
            ->addChild(makeObject(Exception, name("NotFoundException")));

        Root->addChild(makeObject(Object, name("Object"))
            ->addChild(makeObject(assignOperator, name("=")))
            ->addChild(makeObject(referenceAssignOperator, name("<-")))
            ->addChild(makeObject(inherit, name("inherit")))
            ->addChild(makeObject(getParent, name("getParent")))
            ->addChild(makeObject(getChild, name("getChild")))
            ->addChild(makeObject(getChildrenArray, name("getChildrenArray")))
            ->addChild(makeObject(hasChild, name("hasChild")))
            ->addChild(makeObject(removeChild, name("removeChild")))
            ->addChild(makeObject(functionChooser<wrongNumberOfArguments, addChild1, addChild2>, name("addChild")))
            ->addChild(makeObject(getName, name("getName")))
            ->addChild(makeObject(ObjectCopy, name("copy")))
            ->addChild(makeObject(notEqualOperator, name("!=")))
            ->addChild(makeObject(equalReferenceOperator, name("===")))
            //->addChild(makeObject(equalSignaturesTypeOperator, name("sameSignatures")))
            /*->addChild(makeObject(equalInternalTypeOperator, name("====")))*/
            ->addChild(makeObject(debugTree, name("debugTree")))
        );

        Root->addChild(makeObject(Basic, name("Basic"))
            ->addChild(makeObject(nullptr, name("toString")))
            ->addChild(makeObject(nullptr, name("toInt")))
            ->addChild(makeObject(nullptr, name("toDouble")))
            ->addChild(makeObject(nullptr, name("toBoolean")))
        );

        Root->addChild(makeObject(Iterable, name("Iterable"))
            ->addChild(makeObject(nullptr, name("begin")))
            ->addChild(makeObject(nullptr, name("end")))
        );

        Root->addChild(makeObject(Iterator, name("Iterator"))
            ->addChild(makeObject(nullptr, name("++")))
            ->addChild(makeObject(nullptr, name("--")))
            ->addChild(makeObject(nullptr, name("==")))
            ->addChild(makeObject(nullptr, name("<-")))
            ->addChild(makeObject(nullptr, name("get")))
        );

        Root->addChild(makeObject(Container, name("Container"))
            ->addChild(makeObject(nullptr, name("readOperator")))
            ->addChild(makeObject(nullptr, name("size")))
        );

        Root->addChild(makeObject(Int, name("Int"))
            ->addChild(makeObject(IntToString, name("toString")))
            ->addChild(makeObject(IntToInt, name("toInt")))
            ->addChild(makeObject(IntToDouble, name("toDouble")))
            ->addChild(makeObject(IntToBoolean, name("toBoolean")))
            ->addChild(makeObject(binaryOperator<bool, int, std::equal_to>, name("==")))
            ->addChild(makeObject(binaryOperator<bool, int, std::greater>, name(">")))
            ->addChild(makeObject(binaryOperator<bool, int, std::less>, name("<")))
            ->addChild(makeObject(binaryOperator<bool, int, std::greater_equal>, name(">=")))
            ->addChild(makeObject(binaryOperator<bool, int, std::less_equal>, name("<=")))

            ->addChild(makeObject(binaryOperator<int, std::bit_and>, name("&")))
            ->addChild(makeObject(binaryOperator<int, std::bit_or>, name("|")))
            ->addChild(makeObject(binaryOperator<int, std::bit_xor>, name("^")))
            ->addChild(makeObject(unaryOperator<int, std::bit_not>, name("~")))

            ->addChild(makeObject(binaryOperator<int, std::plus>, name("+")))
            ->addChild(makeObject(binaryOperator<int, std::minus>, name("-")))
            ->addChild(makeObject(binaryOperator<int, std::multiplies>, name("*")))
            ->addChild(makeObject(binaryOperator<int, std::divides>, name("/")))
            ->addChild(makeObject(binaryOperator<int, std::modulus>, name("%")))

            ->addChild(makeObject(increment<int>, name("++")))
            ->addChild(makeObject(decrement<int>, name("--")))
        );

        Root->addChild(makeObject(Double, name("Double"))
            ->addChild(makeObject(DoubleToString, name("toString")))
            ->addChild(makeObject(DoubleToInt, name("toInt")))
            ->addChild(makeObject(DoubleToDouble, name("toDouble")))
            ->addChild(makeObject(DoubleToBoolean, name("toBoolean")))
            ->addChild(makeObject(binaryOperator<bool, double, std::equal_to>, name("==")))
            ->addChild(makeObject(binaryOperator<bool, double, std::greater>, name(">")))
            ->addChild(makeObject(binaryOperator<bool, double, std::less>, name("<")))
            ->addChild(makeObject(binaryOperator<bool, double, std::greater_equal>, name(">=")))
            ->addChild(makeObject(binaryOperator<bool, double, std::less_equal>, name("<=")))

            ->addChild(makeObject(binaryOperator<double, std::plus>, name("+")))
            ->addChild(makeObject(binaryOperator<double, std::minus>, name("-")))
            ->addChild(makeObject(binaryOperator<double, std::multiplies>, name("*")))
            ->addChild(makeObject(binaryOperator<double, std::divides>, name("/")))

            ->addChild(makeObject(increment<double>, name("++")))
            ->addChild(makeObject(decrement<double>, name("--")))
        );

        Root->addChild(makeObject(Boolean, name("Boolean"))
            ->addChild(makeObject(BooleanToString, name("toString")))
            ->addChild(makeObject(BooleanToInt, name("toInt")))
            ->addChild(makeObject(BooleanToDouble, name("toDouble")))
            ->addChild(makeObject(BooleanToBoolean, name("toBoolean")))
            ->addChild(makeObject(binaryOperator<bool, std::equal_to>, name("==")))
            ->addChild(makeObject(unaryOperator<bool, std::logical_not>, name("!")))
            ->addChild(makeObject(binaryOperator<bool, std::logical_and>, name("&&")))
            ->addChild(makeObject(binaryOperator<bool, std::logical_or>, name("||")))
        );

        Root
            ->addChild(constructObject(Root, "Boolean", true)->setName(name("true")))
            ->addChild(constructObject(Root, "Boolean", false)->setName(name("false"))
        );

        Root->addChild(makeObject(functionChooser<String0, wrongNumberOfArguments, String2>, name("String"))
            ->addChild(makeObject(StringToString, name("toString")))
            ->addChild(makeObject(StringToInt, name("toInt")))
            ->addChild(makeObject(StringToDouble, name("toDouble")))
            ->addChild(makeObject(StringToBoolean, name("toBoolean")))
            ->addChild(makeObject(StringToAsciiCode, name("toAsciiCode")))
            ->addChild(makeObject(StringReplace, name("replace")))
            ->addChild(makeObject(StringReplaceAll, name("replaceAll")))
            ->addChild(makeObject(method<std::string, std::string::iterator (std::string::*)(), &std::string::begin, std::string::iterator>, name("begin")))
            ->addChild(makeObject(method<std::string, std::string::iterator (std::string::*)(), &std::string::end, std::string::iterator>, name("end")))
            ->addChild(makeObject(StringReadOperator, name("readOperator")))
            ->addChild(makeObject(method<std::string, size_t (std::string::*)() const, &std::string::size, int>, name("size")))
            ->addChild(makeObject(method<std::string, size_t (std::string::*)(const std::string&, size_t) const, &std::string::find, int, std::string, size_t>, name("find")))
            ->addChild(makeObject(method<std::string, bool (std::string::*)() const, &std::string::empty, bool>, name("empty")))
            ->addChild(makeObject(method<std::string, void (std::string::*)(size_t, char), &std::string::resize, void, size_t, char>, name("resize")))
            ->addChild(makeObject(method<std::string, void (std::string::*)(), &std::string::clear, void>, name("clear")))
            ->addChild(makeObject(method<std::string, std::string (std::string::*)(size_t, size_t) const, &std::string::substr, std::string, size_t, size_t>, name("substring")))
            ->addChild(makeObject(method<std::string, std::string::iterator (std::string::*)(std::string::const_iterator, std::string::iterator, std::string::iterator), static_cast<std::string::iterator (std::string::*)(std::string::const_iterator , std::string::iterator, std::string::iterator)>(&std::string::insert<std::string::iterator>), void, std::string::const_iterator, std::string::iterator, std::string::iterator>, name("insert")))
            ->addChild(makeObject(method<std::string, std::string::iterator (std::string::*)(std::string::const_iterator, std::string::const_iterator), static_cast<std::string::iterator (std::string::*)(std::string::const_iterator , std::string::const_iterator)>(&std::string::erase), void, std::string::const_iterator , std::string::const_iterator>, name("erase")))
            ->addChild(makeObject(binaryOperator<bool, std::string, std::equal_to>, name("==")))
            ->addChild(makeObject(binaryOperator<std::string, std::plus>, name("+")))
            ->addChild(makeObject(method<std::string, void (std::string::*)(char), &std::string::push_back, void, char>, name("pushBack")))
            ->addChild(makeObject(binaryOperator<bool, std::string, std::greater>, name(">")))
            ->addChild(makeObject(binaryOperator<bool, std::string, std::less>, name("<")))
            ->addChild(makeObject(binaryOperator<bool, std::string, std::greater_equal>, name(">=")))
            ->addChild(makeObject(binaryOperator<bool, std::string, std::less_equal>, name("<=")))
            /*->addChild(constructObject(Root, "Int", std::string::npos)->setName("maxSize"))*/
        );

        Root->addChild(makeObject(StringIterator, name("StringIterator"))
            //->addChild(makeObject(method<std::string::iterator, std::string::iterator& (std::string::iterator::*)(void), &std::string::iterator::operator++>, name("++")))
            ->addChild(makeObject(increment<std::string::iterator>, name("++")))
            ->addChild(makeObject(decrement<std::string::iterator>, name("--")))
            ->addChild(makeObject(binaryOperator<std::string::iterator, std::string::iterator, int, plus>, name("+")))
            ->addChild(makeObject(binaryOperator<std::string::iterator, std::string::iterator, int, minus>, name("-")))
            ->addChild(makeObject(StringIteratorGet, name("get")))
            ->addChild(makeObject(binaryOperator<bool, std::string::iterator, std::equal_to>, name("==")))
            ->addChild(makeObject(binaryOperator<bool, std::string::iterator, std::greater>, name(">")))
            ->addChild(makeObject(binaryOperator<bool, std::string::iterator, std::less>, name("<")))
            ->addChild(makeObject(binaryOperator<bool, std::string::iterator, std::greater_equal>, name(">=")))
            ->addChild(makeObject(binaryOperator<bool, std::string::iterator, std::less_equal>, name("<=")))
            ->addChild(makeObject(StringIteratorDistance, name("distance")))
            ->addChild(makeObject(StringIteratorReferenceAssignOperator, name("<-")))
        );

        Root->addChild(makeObject(BlockCallable, name("BlockCallable"))
            ->addChild(makeObject(BlockCallableIf, name("if")))
            ->addChild(makeObject(BlockCallableWhile, name("while")))
            ->addChild(makeObject(BlockCallableFor, name("for")))
            ->addChild(makeObject(BlockCallableThrow, name("throw")))
            ->addChild(makeObject(BlockCallableTry, name("try")))
            ->addChild(makeObject(BlockCallableReturn, name("return")))
            ->addChild(makeObject(BlockCallableCallOperator, name("callOperator")))
            ->addChild(makeObject(BlockCallableThis, name("getThis")))
        );

        Root->addChild(makeObject(functionChooser<Array0, Array1, Array2>, name("Array"))
            ->addChild(makeObject(method<std::vector<object::objectPtr>, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(), &std::vector<object::objectPtr>::begin, std::vector<object::objectPtr>::iterator>, name("begin")))
            ->addChild(makeObject(method<std::vector<object::objectPtr>, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(), &std::vector<object::objectPtr>::end, std::vector<object::objectPtr>::iterator>, name("end")))
            ->addChild(makeObject(ArrayReadOperator, name("readOperator")))
            ->addChild(makeObject(function<std::vector<object::objectPtr> (*)(std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator), ArraySubarray, std::vector<object::objectPtr>, std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator>, name("subarray")))
            ->addChild(makeObject(method<std::vector<object::objectPtr>, size_t (std::vector<object::objectPtr>::*)() const, &std::vector<object::objectPtr>::size, int>, name("size")))
            ->addChild(makeObject(ArrayResize, name("resize")))
            ->addChild(makeObject(method<std::vector<object::objectPtr>, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(std::vector<object::objectPtr>::const_iterator , std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator), static_cast<std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(std::vector<object::objectPtr>::const_iterator , std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator)>(&std::vector<object::objectPtr>::insert<std::vector<object::objectPtr>::iterator>), void, std::vector<object::objectPtr>::const_iterator , std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator>, name("insert")))
            ->addChild(makeObject(method<std::vector<object::objectPtr>, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(std::vector<object::objectPtr>::const_iterator , std::vector<object::objectPtr>::const_iterator), static_cast<std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(std::vector<object::objectPtr>::const_iterator , std::vector<object::objectPtr>::const_iterator)>(&std::vector<object::objectPtr>::erase), void, std::vector<object::objectPtr>::const_iterator , std::vector<object::objectPtr>::const_iterator>, name("erase")))
            ->addChild(makeObject(ArrayEqualOperator, name("==")))
            ->addChild(makeObject(ArrayPushBack, name("pushBack")))
        );

        Root->addChild(makeObject(ArrayIterator, name("ArrayIterator"))
            ->addChild(makeObject(increment<std::vector<object::objectPtr>::iterator>, name("++")))
            ->addChild(makeObject(decrement<std::vector<object::objectPtr>::iterator>, name("--")))
            ->addChild(makeObject(binaryOperator<std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator, int, plus>, name("+")))
            ->addChild(makeObject(binaryOperator<std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator, int, minus>, name("-")))
            ->addChild(makeObject(ArrayIteratorGet, name("get")))
            ->addChild(makeObject(binaryOperator<bool, std::vector<object::objectPtr>::iterator, std::equal_to>, name("==")))
            ->addChild(makeObject(binaryOperator<bool, std::vector<object::objectPtr>::iterator, std::greater>, name(">")))
            ->addChild(makeObject(binaryOperator<bool, std::vector<object::objectPtr>::iterator, std::less>, name("<")))
            ->addChild(makeObject(binaryOperator<bool, std::vector<object::objectPtr>::iterator, std::greater_equal>, name(">=")))
            ->addChild(makeObject(binaryOperator<bool, std::vector<object::objectPtr>::iterator, std::less_equal>, name("<=")))
            ->addChild(makeObject(ArrayIteratorDistance, name("distance")))
            ->addChild(makeObject(ArrayIteratorReferenceAssignOperator, name("<-")))
        );

        Root->addChild(makeObject(parse, name("parse"))
        );

        Root->addChild(Root->READ(name("Array"))->CALL()->setName("launchArgs"));
    }
    catch (exception& e)
    {
        Root->READ(name("basicOut"))->CALL(makeObject(e.getMessage(), name("exception")));
    }
}
