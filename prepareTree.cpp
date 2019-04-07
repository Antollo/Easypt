#include "prepareTree.h"

void prepareTree()
{
    object::objectPtr Root = makeObject(nullptr, name("Root"));
    object::objectPtr dot = makeObject(nullptr, name("."))->addChild(Root);
	object::initialize(Root, dot);
    Root->addChild(makeObject(basicOut, name("basicOut")));
        
    //Exception handling ready, here the fun begins
    try
    {
        Root
            ->addChild(makeObject(apply, name("apply")))
            ->addChild(makeObject(call, name("call")))
            ->addChild(makeObject(debugTree, name("debugTree")))
            ->addChild(makeObject(import, name("import")))
            ->addChild(makeObject(instanceOf, name("instanceOf")))
            ->addChild(makeObject(except, name("except")));

        Root->addChild(makeObject(Class, name("Class")))
            ->addChild(makeObject(constructor, name("constructor")));

        
        Root->addChild(makeObject(Exception, name("Exception")))
            ->addChild(makeObject(Exception, name("WrongTypeOfArgumentException")))
            ->addChild(makeObject(Exception, name("WrongNumberOfArgumentsException")))
            ->addChild(makeObject(Exception, name("FileNotFoundException")))
            ->addChild(makeObject(Exception, name("OutOfRangeException")))
            ->addChild(makeObject(Exception, name("NotSupportedOnThisOSException")))
            ->addChild(makeObject(Exception, name("InvalidValueException")))
            ->addChild(makeObject(Exception, name("ParserException")))
            ->addChild(makeObject(Exception, name("NotFoundException")));

        Root->addChild(makeClass({
            makeObject(assignOperator, name("=")),
            makeObject(getParent, name("getParent")), 
            makeObject(getChild, name("getChild")), 
            makeObject(getChildrenArray, name("getChildrenArray")), 
            makeObject(hasChild, name("hasChild")), 
            makeObject(removeChild, name("removeChild")), 
            makeObject(functionChooser<wrongNumberOfArguments, addChild1, addChild2>, name("addChild")), 
            makeObject(getName, name("getName")), 
            makeObject(setName, name("setName")), 
            makeObject(ObjectCopy, name("copy")), 
            makeObject(notEqualOperator, name("!=")), 
            makeObject(equalReferenceOperator, name("===")), 
            makeObject(debugTree, name("debugTree"))
        })->setName("Object"));


        Root->addChild(makeClass({
            Root->READ("Object"),
            makeObject(object::abstractFunction, name("toString")),
            makeObject(object::abstractFunction, name("toInt")),
            makeObject(object::abstractFunction, name("toDouble")),
            makeObject(object::abstractFunction, name("toBoolean"))
        })->setName("Basic"));

        Root->addChild(makeClass({
            Root->READ("Object"),
            makeObject(object::abstractFunction, name("begin")),
            makeObject(object::abstractFunction, name("end"))
        })->setName("Iterable"));

        Root->addChild(makeClass({
            Root->READ("Object"),
            makeObject(object::abstractFunction, name("++")),
            makeObject(object::abstractFunction, name("--")),
            makeObject(object::abstractFunction, name("==")),
            makeObject(object::abstractFunction, name("<-")),
            makeObject(object::abstractFunction, name("get"))
        })->setName("Iterator"));

        Root->addChild(makeClass({
            Root->READ("Iterable"),
            makeObject(object::abstractFunction, name("readOperator")),
            makeObject(object::abstractFunction, name("size"))
        })->setName("Container"));

        Root->addChild(makeClass({
            Root->READ("Basic"),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                obj->getParent()->getValue() = 0;
                return obj->getParent();
            }, name("Int")),
            makeObject(IntToString, name("toString")),
            makeObject(IntToInt, name("toInt")),
            makeObject(IntToDouble, name("toDouble")),
            makeObject(IntToBoolean, name("toBoolean")),
            makeObject(binaryOperator<bool, int, std::equal_to>, name("==")),
            makeObject(binaryOperator<bool, int, std::greater>, name(">")),
            makeObject(binaryOperator<bool, int, std::less>, name("<")),
            makeObject(binaryOperator<bool, int, std::greater_equal>, name(">=")),
            makeObject(binaryOperator<bool, int, std::less_equal>, name("<=")),

            makeObject(binaryOperator<int, std::bit_and>, name("&")),
            makeObject(binaryOperator<int, std::bit_or>, name("|")),
            makeObject(binaryOperator<int, std::bit_xor>, name("^")),
            makeObject(unaryOperator<int, std::bit_not>, name("~")),

            makeObject(binaryOperator<int, std::plus>, name("+")),
            makeObject(binaryOperator<int, std::minus>, name("-")),
            makeObject(binaryOperator<int, std::multiplies>, name("*")),
            makeObject(binaryOperator<int, std::divides>, name("/")),
            makeObject(binaryOperator<int, std::modulus>, name("%")),

            makeObject(increment<int>, name("++")),
            makeObject(decrement<int>, name("--"))
        })->setName("Int"));

        Root->addChild(makeClass({
            Root->READ("Basic"),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                obj->getParent()->getValue() = 0.0;
                return obj->getParent();
            }, name("Double")),
            makeObject(DoubleToString, name("toString")),
            makeObject(DoubleToInt, name("toInt")),
            makeObject(DoubleToDouble, name("toDouble")),
            makeObject(DoubleToBoolean, name("toBoolean")),
            makeObject(binaryOperator<bool, double, std::equal_to>, name("==")),
            makeObject(binaryOperator<bool, double, std::greater>, name(">")),
            makeObject(binaryOperator<bool, double, std::less>, name("<")),
            makeObject(binaryOperator<bool, double, std::greater_equal>, name(">=")),
            makeObject(binaryOperator<bool, double, std::less_equal>, name("<=")),

            makeObject(binaryOperator<double, std::plus>, name("+")),
            makeObject(binaryOperator<double, std::minus>, name("-")),
            makeObject(binaryOperator<double, std::multiplies>, name("*")),
            makeObject(binaryOperator<double, std::divides>, name("/")),

            makeObject(increment<double>, name("++")),
            makeObject(decrement<double>, name("--"))
        })->setName("Double"));

        Root->addChild(makeClass({
            Root->READ("Basic"),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                obj->getParent()->getValue() = false;
                return obj->getParent();
            }, name("Boolean")),
            makeObject(BooleanToString, name("toString")),
            makeObject(BooleanToInt, name("toInt")),
            makeObject(BooleanToDouble, name("toDouble")),
            makeObject(BooleanToBoolean, name("toBoolean")),
            makeObject(binaryOperator<bool, std::equal_to>, name("==")),
            makeObject(unaryOperator<bool, std::logical_not>, name("!")),
            makeObject(binaryOperator<bool, std::logical_and>, name("&&")),
            makeObject(binaryOperator<bool, std::logical_or>, name("||"))
        })->setName("Boolean"));

        Root
            ->addChild(constructObject(Root, "Boolean", true)->setName(name("true")))
            ->addChild(constructObject(Root, "Boolean", false)->setName(name("false")));

        Root->addChild(makeClass({
            Root->READ("Basic"),
            Root->READ("Container"),
            makeObject(functionChooser<String0, wrongNumberOfArguments, String2>, name("String")),
            makeObject(StringToString, name("toString")),
            makeObject(StringToInt, name("toInt")),
            makeObject(StringToDouble, name("toDouble")),
            makeObject(StringToBoolean, name("toBoolean")),
            makeObject(StringToAsciiCode, name("toAsciiCode")),
            makeObject(StringReplace, name("replace")),
            makeObject(StringReplaceAll, name("replaceAll")),
            makeObject(method<std::string, std::string::iterator (std::string::*)() noexcept, &std::string::begin, std::string::iterator>, name("begin")),
            makeObject(method<std::string, std::string::iterator (std::string::*)() noexcept, &std::string::end, std::string::iterator>, name("end")),
            makeObject(StringReadOperator, name("readOperator")),
            makeObject(method<std::string, size_t (std::string::*)() const, &std::string::size, int>, name("size")),
            makeObject(method<std::string, size_t (std::string::*)(const std::string&, size_t) const noexcept, &std::string::find, int, std::string, size_t>, name("find")),
            makeObject(method<std::string, bool (std::string::*)() const, &std::string::empty, bool>, name("empty")),
            makeObject(method<std::string, void (std::string::*)(size_t, char), &std::string::resize, void, size_t, char>, name("resize")),
            makeObject(method<std::string, void (std::string::*)(), &std::string::clear, void>, name("clear")),
            makeObject(method<std::string, std::string (std::string::*)(size_t, size_t) const, &std::string::substr, std::string, size_t, size_t>, name("substring")),
            makeObject(method<std::string, std::string::iterator (std::string::*)(std::string::const_iterator, std::string::iterator, std::string::iterator), static_cast<std::string::iterator (std::string::*)(std::string::const_iterator , std::string::iterator, std::string::iterator)>(&std::string::insert<std::string::iterator>), void, std::string::const_iterator, std::string::iterator, std::string::iterator>, name("insert")),
            makeObject(method<std::string, std::string::iterator (std::string::*)(std::string::const_iterator, std::string::const_iterator), static_cast<std::string::iterator (std::string::*)(std::string::const_iterator , std::string::const_iterator)>(&std::string::erase), void, std::string::const_iterator , std::string::const_iterator>, name("erase")),
            makeObject(binaryOperator<bool, std::string, std::equal_to>, name("==")),
            makeObject(binaryOperator<std::string, std::plus>, name("+")),
            makeObject(method<std::string, void (std::string::*)(char), &std::string::push_back, void, char>, name("pushBack")),
            makeObject(binaryOperator<bool, std::string, std::greater>, name(">")),
            makeObject(binaryOperator<bool, std::string, std::less>, name("<")),
            makeObject(binaryOperator<bool, std::string, std::greater_equal>, name(">=")),
            makeObject(binaryOperator<bool, std::string, std::less_equal>, name("<="))
            /*->addChild(constructObject(Root, "Int", std::string::npos)->setName("maxSize"))*/
        })->setName("String"));

        Root->addChild(makeClass({
            Root->READ("Iterator"),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                obj->getParent()->getValue() = std::string::iterator();
                return obj->getParent();
            }, name("StringIterator")),
            //->addChild(makeObject(method<std::string::iterator, std::string::iterator& (std::string::iterator::*)(void), &std::string::iterator::operator++>, name("++")),
            makeObject(increment<std::string::iterator>, name("++")),
            makeObject(decrement<std::string::iterator>, name("--")),
            makeObject(binaryOperator<std::string::iterator, std::string::iterator, int, plus>, name("+")),
            makeObject(binaryOperator<std::string::iterator, std::string::iterator, int, minus>, name("-")),
            makeObject(StringIteratorGet, name("get")),
            makeObject(binaryOperator<bool, std::string::iterator, std::equal_to>, name("==")),
            makeObject(binaryOperator<bool, std::string::iterator, std::greater>, name(">")),
            makeObject(binaryOperator<bool, std::string::iterator, std::less>, name("<")),
            makeObject(binaryOperator<bool, std::string::iterator, std::greater_equal>, name(">=")),
            makeObject(binaryOperator<bool, std::string::iterator, std::less_equal>, name("<=")),
            makeObject(StringIteratorDistance, name("distance")),
            makeObject(StringIteratorReferenceAssignOperator, name("<-"))
        })->setName("StringIterator"));

        Root->addChild(makeClass({
            Root->READ("Object"),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                obj->getParent()->getValue() = std::list<expression>();
                obj->getParent()->addSignature(name("Callable"));
                return obj->getParent();
            }, name("BlockCallable")),
            makeObject(BlockCallableIf, name("if")),
            makeObject(BlockCallableWhile, name("while")),
            makeObject(BlockCallableFor, name("for")),
            makeObject(BlockCallableThrow, name("throw")),
            makeObject(BlockCallableTry, name("try")),
            makeObject(BlockCallableReturn, name("return")),
            makeObject(BlockCallableCallOperator, name("callOperator")),
            makeObject(BlockCallableThis, name("getThis"))
        })->setName("BlockCallable"));

        Root->addChild(makeClass({
            Root->READ("Container"),
            makeObject(functionChooser<Array0, Array1, Array2>, name("Array")),
            makeObject(method<object::arrayType, object::arrayType::iterator (object::arrayType::*)() noexcept, &object::arrayType::begin, object::arrayType::iterator>, name("begin")),
            makeObject(method<object::arrayType, object::arrayType::iterator (object::arrayType::*)() noexcept, &object::arrayType::end, object::arrayType::iterator>, name("end")),
            makeObject(ArrayReadOperator, name("readOperator")),
            makeObject(function<object::arrayType (*)(object::arrayType::iterator, object::arrayType::iterator), ArraySubarray, object::arrayType, object::arrayType::iterator, object::arrayType::iterator>, name("subarray")),
            makeObject(method<object::arrayType, size_t (object::arrayType::*)() const, &object::arrayType::size, int>, name("size")),
            makeObject(ArrayResize, name("resize")),
            makeObject(method<object::arrayType, object::arrayType::iterator (object::arrayType::*)(object::arrayType::const_iterator , object::arrayType::iterator, object::arrayType::iterator), static_cast<object::arrayType::iterator (object::arrayType::*)(object::arrayType::const_iterator , object::arrayType::iterator, object::arrayType::iterator)>(&object::arrayType::insert<object::arrayType::iterator>), void, object::arrayType::const_iterator , object::arrayType::iterator, object::arrayType::iterator>, name("insert")),
            makeObject(method<object::arrayType, object::arrayType::iterator (object::arrayType::*)(object::arrayType::const_iterator , object::arrayType::const_iterator), static_cast<object::arrayType::iterator (object::arrayType::*)(object::arrayType::const_iterator , object::arrayType::const_iterator)>(&object::arrayType::erase), void, object::arrayType::const_iterator , object::arrayType::const_iterator>, name("erase")),
            makeObject(ArrayEqualOperator, name("==")),
            makeObject(ArrayPushBack, name("pushBack"))
        })->setName("Array"));

        Root->addChild(makeClass({
            Root->READ("Iterator"),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                obj->getParent()->getValue() = object::arrayType::iterator();
                return obj->getParent();
            }, name("ArrayIterator")),
            makeObject(increment<object::arrayType::iterator>, name("++")),
            makeObject(decrement<object::arrayType::iterator>, name("--")),
            makeObject(binaryOperator<object::arrayType::iterator, object::arrayType::iterator, int, plus>, name("+")),
            makeObject(binaryOperator<object::arrayType::iterator, object::arrayType::iterator, int, minus>, name("-")),
            makeObject(ArrayIteratorGet, name("get")),
            makeObject(binaryOperator<bool, object::arrayType::iterator, std::equal_to>, name("==")),
            makeObject(binaryOperator<bool, object::arrayType::iterator, std::greater>, name(">")),
            makeObject(binaryOperator<bool, object::arrayType::iterator, std::less>, name("<")),
            makeObject(binaryOperator<bool, object::arrayType::iterator, std::greater_equal>, name(">=")),
            makeObject(binaryOperator<bool, object::arrayType::iterator, std::less_equal>, name("<=")),
            makeObject(ArrayIteratorDistance, name("distance")),
            makeObject(ArrayIteratorReferenceAssignOperator, name("<-"))
        })->setName("ArrayIterator"));

        Root->addChild(makeClass({
            Root->READ("Object"),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                obj->getParent()->getValue() = std::make_shared<SequentialTask::Future<object::objectPtr>>(SequentialTask::makeSequentialTask([obj, args]()-> object::objectPtr {
                    object::arrayType temp(args);
                    return call(obj, temp);
                }));
                return obj->getParent();
            }, name("Task")),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                return (*std::any_cast<std::shared_ptr<SequentialTask::Future<object::objectPtr>>>(&obj->getParent()->getValue()))->get();
            }, name("get")),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                return constructObject(obj, "Boolean", (*std::any_cast<std::shared_ptr<SequentialTask::Future<object::objectPtr>>>(&obj->getParent()->getValue()))->valid());
            }, name("isValid")),
            makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
                return constructObject(obj, "Boolean", (*std::any_cast<std::shared_ptr<SequentialTask::Future<object::objectPtr>>>(&obj->getParent()->getValue()))->ready());
            }, name("isReady"))
        })->setName("Task")
            //->addChild(makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
            //    
            //}, name(setPriority)))
        );


        Root->addChild(makeObject(parse, name("parse")));

        Root->addChild(Root->READ(name("Array"))->CALL()->setName("launchArgs"));
    }
    catch (exception& e)
    {
        Root->READ(name("basicOut"))->CALL(makeObject(e.getMessage(), name("preStringException")));
    }
    catch (std::exception& e)
    {
        Root->READ(name("basicOut"))->CALL(makeObject("Unknown exception: " + std::string(e.what()), name("preStringException")));
    }
    catch (object::objectPtr& e)
    {
		Root->READ(name("basicOut"))->CALL(e);
    }
}
