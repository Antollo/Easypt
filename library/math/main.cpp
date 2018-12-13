#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "nobject.h"

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

extern "C"
{
    EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args);
}

template<class S, S f>
object::objectPtr MFunction0 (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() != 0)
        throw(WrongNumberOfArguments("Wrong number of arguments"));
    return constructObject(obj, "Double", (double) f());
}

template<class S, S f>
object::objectPtr MFunction1 (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() != 1)
        throw(WrongNumberOfArguments("Wrong number of arguments"));
    if (args[0]->getValue().type().hash_code() == typeid(double).hash_code())
        return constructObject(obj, "Double", f(std::any_cast<double>(args[0]->getValue())));
    else if (args[0]->getValue().type().hash_code() == typeid(int).hash_code())
        return constructObject(obj, "Double", (double) f((double) std::any_cast<int>(args[0]->getValue())));
    else
        throw(WrongTypeOfArgument("Wrong type of argument"));
}

template<class S, S f>
object::objectPtr MFunction2 (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() != 2)
    throw(WrongNumberOfArguments("Wrong number of arguments"));
    double a1, a2;
    if (args[0]->getValue().type().hash_code() == typeid(double).hash_code())
        a1 = std::any_cast<double>(args[0]->getValue());
    else if (args[0]->getValue().type().hash_code() == typeid(int).hash_code())
        a1 = std::any_cast<int>(args[0]->getValue());
    else
        throw(WrongTypeOfArgument("Wrong type of argument"));
    if (args[1]->getValue().type().hash_code() == typeid(double).hash_code())
        a2 = std::any_cast<double>(args[1]->getValue());
    else if (args[1]->getValue().type().hash_code() == typeid(int).hash_code())
        a2 = std::any_cast<int>(args[1]->getValue());
    else
        throw(WrongTypeOfArgument("Wrong type of argument"));
    return constructObject(obj, "Double", (double) f(a1, a2));
}

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args)
{
    std::srand(std::time(0));

    name::initialize(std::any_cast<name::initializationPack>(args[0]->getValue()));
    object::initialize(obj->READ(name("Root"), true));

    obj->addChild(constructObject(obj, "Double", M_E)->setName(name("e")))
        ->addChild(constructObject(obj, "Double", M_PI)->setName(name("pi")))
        ->addChild(makeObject(MFunction0<int (*)(), std::rand>, name("random")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::abs>, name("abs")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::acos>, name("acos")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::asin>, name("asin")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::atan>, name("atan")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::ceil>, name("ceil")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::sin>, name("sin")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::cos>, name("cos")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::tan>, name("tan")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::exp>, name("exp")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::floor>, name("floor")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::log>, name("log")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::log10>, name("log10")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::log2>, name("log2")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::round>, name("round")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::sqrt>, name("sqrt")))
        ->addChild(makeObject(MFunction1<double (*)(double), std::cbrt>, name("cbrt")))
        ->addChild(makeObject(MFunction2<double (*)(double, double), std::atan2>, name("atan2")))
        ->addChild(makeObject(MFunction2<double (*)(double, double), std::pow>, name("pow")));
    return nullptr;
}
