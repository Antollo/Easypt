#ifndef COMMON_H
#define COMMON_H

#include "nobject.h"
#include "parser.h"
#include <tuple>

object::objectPtr parse (object::objectPtr obj, object::argsContainer& args);
object::objectPtr errorOut (object::objectPtr obj, object::argsContainer& args);
object::objectPtr WrongNumberOfArguments (object::objectPtr obj, object::argsContainer& args);

namespace typeNames
{
    extern const char Object[];
    extern const char String[];
    extern const char StringIterator[];
    extern const char Int[];
    extern const char Boolean[];
    extern const char Double[];
    extern const char Array[];
    extern const char ArrayIterator[];
    extern const char BlockCallable[];
}

//Templated functions
template<class T, template<class> class OP, const char* STR>
object::objectPtr T2TOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name(STR)))
        {
            object::objectPtr ret = obj->READ(name(STR), true)->CALL();
            ret->getValue() = OP<T>()(std::any_cast<T>(obj->getParent()->getValue()), std::any_cast<T>(args[0]->getValue()));
            return ret;
        }
        throw(exception("Argument is not ", STR," in ", obj->getFullNameString()));
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
template<class T, template<class> class OP, const char* STR>
object::objectPtr T2BOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name(STR)))
        {
            object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
            ret->getValue() = OP<T>()(std::any_cast<T>(obj->getParent()->getValue()), std::any_cast<T>(args[0]->getValue()));
            return ret;
        }
        throw(exception("Argument is not ", STR," in ", obj->getFullNameString()));
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
template<class T, template<class> class OP, const char* STR>
object::objectPtr T1TOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 0)
    {
        object::objectPtr ret = obj->READ(name(STR), true)->CALL();
        ret->getValue() = OP<T>()(std::any_cast<T>(obj->getParent()->getValue()));
        return ret;
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

//Template for everything
bool isTrue();
bool isTrue(bool first);

template<class... Args>
bool isTrue(bool first, Args... args)
{
    return first && isTrue(args...);
}

template<int... Is>
struct seq { };

template<int N, int... Is>
struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

template<int... Is>
struct gen_seq<0, Is...> : seq<Is...> { };

template<class T>
struct guess_type
{
	typedef typename std::conditional<
	std::is_integral<T>::value, int,
		typename std::conditional<std::is_floating_point<T>::value, double,T>::type
	>::type type;
};


template<class V, class R, class... Args, int... Is>
R callMethod(V* value, R (V::*f)(Args...), object::argsContainer& args, seq<Is...>)
{
    if (isTrue((args[Is]->getValue().type().hash_code() == typeid(typename guess_type<Args>::type).hash_code())...))
        return (value->*f)(*std::any_cast<typename guess_type<Args>::type>(&args[Is]->getValue())...);
    throw(exception("Wrong types of arguments"));
}

template<class V, class R, class... Args, int... Is>
R callMethod(V* value, R (V::*f)(Args...) const, object::argsContainer& args, seq<Is...>)
{
    if (isTrue((args[Is]->getValue().type().hash_code() == typeid(typename guess_type<Args>::type).hash_code())...))
        return (value->*f)(*std::any_cast<typename guess_type<Args>::type>(&args[Is]->getValue())...);
    throw(exception("Wrong types of arguments"));
}

template<class R, class... Args, int... Is>
R callFunction(R (*f)(Args...), object::argsContainer& args, seq<Is...>)
{
    if (isTrue((args[Is]->getValue().type().hash_code() == typeid(typename guess_type<Args>::type).hash_code())...))
        return f(*std::any_cast<typename guess_type<Args>::type>(&args[Is]->getValue())...);
    throw(exception("Wrong types of arguments"));
}

template<class V, class S, S f, class R, const char* typeName,  class... Args>
object::objectPtr TMethod (object::objectPtr obj, object::argsContainer& args)
{
    return obj->READ(name(typeName), true)->CALL()->setValue((R) callMethod(std::any_cast<V>(&obj->getParent()->getValue()), f, args, gen_seq<sizeof...(Args)>()));
}

template<class V, class S, S f,  class... Args>
object::objectPtr VMethod (object::objectPtr obj, object::argsContainer& args)
{
    callMethod(std::any_cast<V>(&obj->getParent()->getValue()), f, args, gen_seq<sizeof...(Args)>());
    return obj->getParent();
}

template<class S, S f, class R, const char* typeName,  class... Args>
object::objectPtr TFunction (object::objectPtr obj, object::argsContainer& args)
{
    return obj->READ(name(typeName), true)->CALL()->setValue((R) callFunction(f, args, gen_seq<sizeof...(Args)>()));
}

template<class S, S f, class... Args>
object::objectPtr VFunction (object::objectPtr obj, object::argsContainer& args)
{
    callFunction(f, args, gen_seq<sizeof...(Args)>());
    return obj->getParent();
}

typedef object::objectPtr (*Ftype)(object::objectPtr, object::argsContainer&);
template<Ftype... F>
object::objectPtr FunctionChooser (object::objectPtr obj, object::argsContainer& args)
{
    Ftype functions[sizeof...(F)] = {F...};
    if (args.size() < sizeof...(F))
        return functions[args.size()](obj, args);
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

//Additional template functions
template <class T>
object::objectPtr increment (object::objectPtr obj, object::argsContainer& args)
{
    (*std::any_cast<T>(&obj->getParent()->getValue()))++;
    return obj->getParent();
}
template <class T>
object::objectPtr decrement (object::objectPtr obj, object::argsContainer& args)
{
    (*std::any_cast<T>(&obj->getParent()->getValue()))--;
    return obj->getParent();
}

#endif
