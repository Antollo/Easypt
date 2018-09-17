#include "prepareTree.h"

std::pair<object::objectPtr, object::objectPtr> prepareTree()
{
    object::objectPtr Root = makeObject(nullptr, name("Root"));
    object::initialize(Root);
    object::objectPtr dot = makeObject(nullptr, name("."))->addChild(Root);

    Root
        ->addChild(makeObject(basicOut, name("basicOut")))
        ->addChild(makeObject(debugTree, name("debugTree")))
        ->addChild(makeObject(import, name("import")));
    //Exception handling ready, here the fun starts
    try
    {
        Root->addChild(makeObject(Exception, name("WrongTypeOfArgumentException")))
            ->addChild(makeObject(Exception, name("WrongNumberOfArgumentsException")))
            ->addChild(makeObject(Exception, name("FileNotFoundException")))
            ->addChild(makeObject(Exception, name("OutOfRangeException")))
            ->addChild(makeObject(Exception, name("NotSupportedOnThisOSException")))
            ->addChild(makeObject(Exception, name("InvalidValueException")))
            ->addChild(makeObject(Exception, name("ParserException")))
            ->addChild(makeObject(Exception, name("NotFoundException")));

        Root->addChild(makeObject(Object, name("Object"))
            ->addChild(makeObject(assignOperator, name("=")))
            ->addChild(makeObject(instanceOf, name("instanceOf")))
            ->addChild(makeObject(merge, name("merge")))
            ->addChild(makeObject(getParent, name("getParent")))
            ->addChild(makeObject(getChild, name("getChild")))
            ->addChild(makeObject(hasChild, name("hasChild")))
            ->addChild(makeObject(FunctionChooser<wrongNumberOfArguments, addChild1, addChild2>, name("addChild")))
            ->addChild(makeObject(getName, name("getName")))
            ->addChild(makeObject(copy, name("copy")))
            ->addChild(makeObject(notEqualOperator, name("!=")))
            ->addChild(makeObject(equalReferenceOperator, name("==")))
            ->addChild(makeObject(equalSignaturesTypeOperator, name("===")))
            ->addChild(makeObject(equalInternalTypeOperator, name("====")))
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
            ->addChild(makeObject(nullptr, name("+")))
            ->addChild(makeObject(nullptr, name("-")))
            ->addChild(makeObject(nullptr, name("==")))
            ->addChild(makeObject(nullptr, name("=")))
            ->addChild(makeObject(nullptr, name("get")))
        );

        Root->addChild(makeObject(Container, name("Container"))
            ->addChild(makeObject(nullptr, name("readOperator")))
            ->addChild(makeObject(nullptr, name("size")))
        );

        Root->addChild(makeObject(String, name("String"))
            ->addChild(makeObject(StringToString, name("toString")))
            ->addChild(makeObject(StringToInt, name("toInt")))
            ->addChild(makeObject(StringToDouble, name("toDouble")))
            ->addChild(makeObject(StringToBoolean, name("toBoolean")))
            ->addChild(makeObject(TMethod<std::string, std::string::iterator (std::string::*)(), &std::string::begin, std::string::iterator, typeNames::StringIterator>, name("begin")))
            ->addChild(makeObject(TMethod<std::string, std::string::iterator (std::string::*)(), &std::string::end, std::string::iterator, typeNames::StringIterator>, name("end")))
            ->addChild(makeObject(StringReadOperator, name("readOperator")))
            ->addChild(makeObject(TMethod<std::string, size_t (std::string::*)() const, &std::string::size, int, typeNames::Int>, name("size")))
            ->addChild(makeObject(TMethod<std::string, size_t (std::string::*)(const std::string&, size_t) const, &std::string::find, int, typeNames::Int, std::string, size_t>, name("find")))
            ->addChild(makeObject(TMethod<std::string, bool (std::string::*)() const, &std::string::empty, bool, typeNames::Boolean>, name("empty")))
            ->addChild(makeObject(VMethod<std::string, void (std::string::*)(size_t, char), &std::string::resize, size_t, char>, name("resize")))
            ->addChild(makeObject(VMethod<std::string, void (std::string::*)(), &std::string::clear>, name("clear")))
            ->addChild(makeObject(TMethod<std::string, std::string (std::string::*)(size_t, size_t) const, &std::string::substr, std::string, typeNames::String, size_t, size_t>, name("substring")))
            ->addChild(makeObject(VMethod<std::string, std::string::iterator (std::string::*)(std::string::const_iterator , std::string::iterator, std::string::iterator), static_cast<std::string::iterator (std::string::*)(std::string::const_iterator , std::string::iterator, std::string::iterator)>(&std::string::insert<std::string::iterator>), std::string::const_iterator , std::string::iterator, std::string::iterator>, name("insert")))
            ->addChild(makeObject(VMethod<std::string, std::string::iterator (std::string::*)(std::string::const_iterator , std::string::const_iterator), static_cast<std::string::iterator (std::string::*)(std::string::const_iterator , std::string::const_iterator)>(&std::string::erase), std::string::const_iterator , std::string::const_iterator>, name("erase")))
            ->addChild(makeObject(T2BOperator<std::string, std::equal_to, typeNames::String>, name("==")))
            ->addChild(makeObject(T2TOperator<std::string, std::plus, typeNames::String>, name("+")))
        );

        Root->addChild(makeObject(StringIterator, name("StringIterator"))
            //->addChild(makeObject(VMethod<std::string::iterator, std::string::iterator& (std::string::iterator::*)(void), &std::string::iterator::operator++>, name("++")))
            ->addChild(makeObject(increment<std::string::iterator>, name("++")))
            ->addChild(makeObject(decrement<std::string::iterator>, name("--")))
            ->addChild(makeObject(TMethod<std::string::iterator, std::string::iterator (std::string::iterator::*)(int) const, &std::string::iterator::operator+, std::string::iterator, typeNames::StringIterator, int>, name("+")))
            ->addChild(makeObject(TMethod<std::string::iterator, std::string::iterator (std::string::iterator::*)(int) const, &std::string::iterator::operator-, std::string::iterator, typeNames::StringIterator, int>, name("-")))
            ->addChild(makeObject(StringIteratorGet, name("get")))
            ->addChild(makeObject(T2BOperator<std::string::iterator, std::equal_to, typeNames::StringIterator>, name("==")))
            ->addChild(makeObject(T2BOperator<std::string::iterator, std::greater, typeNames::StringIterator>, name(">")))
            ->addChild(makeObject(T2BOperator<std::string::iterator, std::less, typeNames::StringIterator>, name("<")))
            ->addChild(makeObject(T2BOperator<std::string::iterator, std::greater_equal, typeNames::StringIterator>, name(">=")))
            ->addChild(makeObject(T2BOperator<std::string::iterator, std::less_equal, typeNames::StringIterator>, name("<=")))
            ->addChild(makeObject(StringIteratorAssignOperator, name("=")))
        );

        Root->addChild(makeObject(Int, name("Int"))
            ->addChild(makeObject(IntToString, name("toString")))
            ->addChild(makeObject(IntToInt, name("toInt")))
            ->addChild(makeObject(IntToDouble, name("toDouble")))
            ->addChild(makeObject(IntToBoolean, name("toBoolean")))
            ->addChild(makeObject(T2BOperator<int, std::equal_to, typeNames::Int>, name("==")))
            ->addChild(makeObject(T2BOperator<int, std::greater, typeNames::Int>, name(">")))
            ->addChild(makeObject(T2BOperator<int, std::less, typeNames::Int>, name("<")))
            ->addChild(makeObject(T2BOperator<int, std::greater_equal, typeNames::Int>, name(">=")))
            ->addChild(makeObject(T2BOperator<int, std::less_equal, typeNames::Int>, name("<=")))

            ->addChild(makeObject(T2TOperator<int, std::bit_and, typeNames::Int>, name("&")))
            ->addChild(makeObject(T2TOperator<int, std::bit_or, typeNames::Int>, name("|")))
            ->addChild(makeObject(T2TOperator<int, std::bit_xor, typeNames::Int>, name("^")))
            ->addChild(makeObject(T1TOperator<int, std::bit_not, typeNames::Int>, name("~")))

            ->addChild(makeObject(T2TOperator<int, std::plus, typeNames::Int>, name("+")))
            ->addChild(makeObject(T2TOperator<int, std::minus, typeNames::Int>, name("-")))
            ->addChild(makeObject(T2TOperator<int, std::multiplies, typeNames::Int>, name("*")))
            ->addChild(makeObject(T2TOperator<int, std::divides, typeNames::Int>, name("/")))
            ->addChild(makeObject(T2TOperator<int, std::modulus, typeNames::Int>, name("%")))

            ->addChild(makeObject(increment<int>, name("++")))
            ->addChild(makeObject(decrement<int>, name("--")))
        );

        Root->addChild(makeObject(Double, name("Double"))
            ->addChild(makeObject(DoubleToString, name("toString")))
            ->addChild(makeObject(DoubleToInt, name("toInt")))
            ->addChild(makeObject(DoubleToDouble, name("toDouble")))
            ->addChild(makeObject(DoubleToBoolean, name("toBoolean")))
            ->addChild(makeObject(T2BOperator<double, std::equal_to, typeNames::Double>, name("==")))
            ->addChild(makeObject(T2BOperator<double, std::greater, typeNames::Double>, name(">")))
            ->addChild(makeObject(T2BOperator<double, std::less, typeNames::Double>, name("<")))
            ->addChild(makeObject(T2BOperator<double, std::greater_equal, typeNames::Double>, name(">=")))
            ->addChild(makeObject(T2BOperator<double, std::less_equal, typeNames::Double>, name("<=")))

            ->addChild(makeObject(T2TOperator<double, std::plus, typeNames::Double>, name("+")))
            ->addChild(makeObject(T2TOperator<double, std::minus, typeNames::Double>, name("-")))
            ->addChild(makeObject(T2TOperator<double, std::multiplies, typeNames::Double>, name("*")))
            ->addChild(makeObject(T2TOperator<double, std::divides, typeNames::Double>, name("/")))

            ->addChild(makeObject(increment<double>, name("++")))
            ->addChild(makeObject(decrement<double>, name("--")))
        );

        Root->addChild(makeObject(Boolean, name("Boolean"))
            ->addChild(makeObject(BooleanToString, name("toString")))
            ->addChild(makeObject(BooleanToInt, name("toInt")))
            ->addChild(makeObject(BooleanToDouble, name("toDouble")))
            ->addChild(makeObject(BooleanToBoolean, name("toBoolean")))
            ->addChild(makeObject(T2BOperator<bool, std::equal_to, typeNames::Boolean>, name("==")))
            ->addChild(makeObject(T1TOperator<bool, std::logical_not, typeNames::Boolean>, name("!")))
        );

        Root
            ->addChild(constructObject(Root, "Boolean", true)->setName(name("true")))
            ->addChild(constructObject(Root, "Boolean", false)->setName(name("false")));

        Root->addChild(makeObject(BlockCallable, name("BlockCallable"))
            ->addChild(makeObject(BlockCallableIf, name("if")))
            ->addChild(makeObject(BlockCallableWhile, name("while")))
            ->addChild(makeObject(BlockCallableFor, name("for")))
            ->addChild(makeObject(BlockCallableThrow, name("throw")))
            ->addChild(makeObject(BlockCallableTry, name("try")))
            ->addChild(makeObject(BlockCallableCallOperator, name("callOperator")))
            ->addChild(makeObject(T2BOperator<std::list<expression>, std::equal_to, typeNames::BlockCallable>, name("==")))
        );

        Root->addChild(makeObject(FunctionChooser<Array0, Array1, Array2>, name("Array"))
            ->addChild(makeObject(TMethod<std::vector<object::objectPtr>, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(), &std::vector<object::objectPtr>::begin, std::vector<object::objectPtr>::iterator, typeNames::ArrayIterator>, name("begin")))
            ->addChild(makeObject(TMethod<std::vector<object::objectPtr>, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::*)(), &std::vector<object::objectPtr>::end, std::vector<object::objectPtr>::iterator, typeNames::ArrayIterator>, name("end")))
            ->addChild(makeObject(ArrayReadOperator, name("readOperator")))
            ->addChild(makeObject(TMethod<std::vector<object::objectPtr>, size_t (std::vector<object::objectPtr>::*)() const, &std::vector<object::objectPtr>::size, int, typeNames::Int>, name("size")))
            ->addChild(makeObject(VMethod<std::vector<object::objectPtr>, void (std::vector<object::objectPtr>::*)(size_t), &std::vector<object::objectPtr>::resize, int>, name("resize")))
            ->addChild(makeObject(T2BOperator< std::vector<object::objectPtr>, std::equal_to, typeNames::Array>, name("==")))
            ->addChild(makeObject(ArrayPushBack, name("pushBack")))
        );

        Root->addChild(makeObject(ArrayIterator, name("ArrayIterator"))
            ->addChild(makeObject(increment<std::vector<object::objectPtr>::iterator>, name("++")))
            ->addChild(makeObject(decrement<std::vector<object::objectPtr>::iterator>, name("--")))
            ->addChild(makeObject(TMethod<std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::iterator::*)(int) const, &std::vector<object::objectPtr>::iterator::operator+, std::vector<object::objectPtr>::iterator, typeNames::ArrayIterator, int>, name("+")))
            ->addChild(makeObject(TMethod<std::vector<object::objectPtr>::iterator, std::vector<object::objectPtr>::iterator (std::vector<object::objectPtr>::iterator::*)(int) const, &std::vector<object::objectPtr>::iterator::operator-, std::vector<object::objectPtr>::iterator, typeNames::ArrayIterator, int>, name("-")))
            ->addChild(makeObject(ArrayIteratorGet, name("get")))
            ->addChild(makeObject(T2BOperator<std::vector<object::objectPtr>::iterator, std::equal_to, typeNames::ArrayIterator>, name("==")))
            ->addChild(makeObject(T2BOperator<std::vector<object::objectPtr>::iterator, std::greater, typeNames::ArrayIterator>, name(">")))
            ->addChild(makeObject(T2BOperator<std::vector<object::objectPtr>::iterator, std::less, typeNames::ArrayIterator>, name("<")))
            ->addChild(makeObject(T2BOperator<std::vector<object::objectPtr>::iterator, std::greater_equal, typeNames::ArrayIterator>, name(">=")))
            ->addChild(makeObject(T2BOperator<std::vector<object::objectPtr>::iterator, std::less_equal, typeNames::ArrayIterator>, name("<=")))
            ->addChild(makeObject(ArrayIteratorAssignOperator, name("=")))
        );

        Root->addChild(makeObject(parse, name("parse"))
        );

        Root->addChild(Root->READ(name("Array"))->CALL()->setName("launchArgs"));
    }
    catch (exception& e)
    {
        Root->READ(name("basicOut"))->CALL(makeObject(e.getMessage(), name("exception")));
    }

    return std::make_pair(dot, Root);
}
