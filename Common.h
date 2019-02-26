#ifndef COMMON_H
#define COMMON_H

#include "nobject.h"
#include "parser.h"

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

template<class T>
struct guessTypeName
{
    static constexpr const char* name = "WrongType";
};

template<class T>
struct guessTypeName<const T> : guessTypeName<T> {};

template<class T>
struct guessTypeName<T&> : guessTypeName<T> {};

template<class T>
struct guessTypeName<T&&> : guessTypeName<T> {};

template<>
struct guessTypeName<void>
{
    static constexpr const char* name = typeNames::Object;
};

template<>
struct guessTypeName<std::string>
{
    static constexpr const char* name = typeNames::String;
};

template<>
struct guessTypeName<std::string::iterator>
{
    static constexpr const char* name = typeNames::StringIterator;
};

template<>
struct guessTypeName<int>
{
    static constexpr const char* name = typeNames::Int;
};

template<>
struct guessTypeName<bool>
{
    static constexpr const char* name = typeNames::Boolean;
};

template<>
struct guessTypeName<double>
{
    static constexpr const char* name = typeNames::Double;
};

template<>
struct guessTypeName<object::argsContainer>
{
    static constexpr const char* name = typeNames::Array;
};

template<>
struct guessTypeName<object::argsContainer::iterator>
{
    static constexpr const char* name = typeNames::ArrayIterator;
};

template<>
struct guessTypeName<std::list<expression>>
{
    static constexpr const char* name = typeNames::BlockCallable;
};

template<class T1, class T2>
struct plus
{
    T1 operator()(const T1& t, const T2& x)
    {
        return t + x;
    }
};

template<class T1, class T2>
struct minus
{
    T1 operator()(const T1& t, const T2& x)
    {
        return t - x;
    }
};

template<class R, class T1, class T2, template<class, class> class OP>
object::objectPtr binaryOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(guessTypeName<T2>::name))
        {
            object::objectPtr ret = obj->READ(guessTypeName<R>::name, true)->CALL();
            ret->getValue() = (R) OP<T1, T2>()(std::any_cast<T1>(obj->getParent()->getValue()), std::any_cast<T2>(args[0]->getValue()));
            return ret;
        }
        throw(WrongTypeOfArgument("Argument is not ", guessTypeName<T2>::name," in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

template<class R, class T, template<class> class OP>
object::objectPtr binaryOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(guessTypeName<T>::name))
        {
            if (std::is_same<OP<T>, std::divides<int>>::value || std::is_same<OP<T>, std::modulus<int>>::value)
            {
                if (std::any_cast<int>(args[0]->getValue()) == 0)
                    throw(Arithmetic("Division by zero while calling ", obj->getFullNameString()));
            }
            object::objectPtr ret = obj->READ(guessTypeName<R>::name, true)->CALL();
            ret->getValue() = (R) OP<T>()(std::any_cast<T>(obj->getParent()->getValue()), std::any_cast<T>(args[0]->getValue()));
            return ret;  
        }
        throw(WrongTypeOfArgument("Argument is not ", guessTypeName<T>::name," in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

template<class T, template<class> class OP>
object::objectPtr binaryOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(guessTypeName<T>::name))
        {
            if (std::is_same<OP<T>, std::divides<int>>::value || std::is_same<OP<T>, std::modulus<int>>::value)
            {
                if (std::any_cast<int>(args[0]->getValue()) == 0)
                    throw(Arithmetic("Division by zero while calling ", obj->getFullNameString()));
            }
            object::objectPtr ret = obj->READ(guessTypeName<T>::name, true)->CALL();
            ret->getValue() = (T) OP<T>()(std::any_cast<T>(obj->getParent()->getValue()), std::any_cast<T>(args[0]->getValue()));
            return ret;  
        }
        throw(WrongTypeOfArgument("Argument is not ", guessTypeName<T>::name," in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

template<class T, template<class> class OP>
object::objectPtr unaryOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 0)
    {
        object::objectPtr ret = obj->READ(guessTypeName<T>::name, true)->CALL();
        ret->getValue() = (T) OP<T>()(std::any_cast<T>(obj->getParent()->getValue()));
        return ret;
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

bool isTrue();
bool isTrue(bool first);

template<class... Args>
bool isTrue(bool first, Args... args)
{
    return first && isTrue(args...);
}

template<class T>
struct guessType
{
	using type = typename std::conditional<
	    std::is_integral<T>::value, int,
		    typename std::conditional<std::is_floating_point<T>::value, double, T>::type
	>::type;
};

template<>
struct guessType<char>
{
    using type = std::string;
};

template<>
struct guessType<std::string::const_iterator>
{
    using type = std::string::iterator;
};

template<>
struct guessType<std::vector<object::objectPtr>::const_iterator>
{
    using type = std::vector<object::objectPtr>::iterator;
};

template<class T>
using guessTypeT = typename guessType<T>::type;

template<class>
struct resultOf {};

template<class R, class... Args>
struct resultOf<R (*)(Args...)>
{
    using type = R;
};

template<class O, class R, class... Args>
struct resultOf<R (O::*)(Args...)>
{
    using type = R;
};

template<class O, class R, class... Args>
struct resultOf<R (O::*)(Args...) const>
{
    using type = R;
};

template<class... Args>
using resultOfT = typename resultOf<Args...>::type;

template<class R, class A>
inline R typeConverter(const A& a)
{
    return (R)a;
};

template<class T>
inline T& typeConverter(T& t)
{
    return t;
};

template<>
inline char typeConverter(const std::string& str)
{
    if (str.empty())
        throw(OutOfRange("Out of range"));
    return str[0];
};

template<class O, class R, class... Args, std::size_t... Is>
R callMethod(O* obj, R (O::*f)(Args...), object::argsContainer& args, std::index_sequence<Is...>)
{
    if (isTrue((args[Is]->getValue().type().hash_code() == typeid(typename guessType<Args>::type).hash_code())...))
        return (obj->*f)((typeConverter<Args, typename guessType<Args>::type>(*std::any_cast<typename guessType<Args>::type>(&args[Is]->getValue())))...);
    throw(WrongTypeOfArgument("Wrong type of argument"));
}

template<class O, class R, class... Args, std::size_t... Is>
R callMethod(O* obj, R (O::*f)(Args...) const, object::argsContainer& args, std::index_sequence<Is...>)
{
    if (isTrue((args[Is]->getValue().type().hash_code() == typeid(typename guessType<Args>::type).hash_code())...))
        return (obj->*f)((typeConverter<Args, typename guessType<Args>::type>(std::any_cast<typename guessType<Args>::type>(args[Is]->getValue())))...);
    throw(WrongTypeOfArgument("Wrong type of argument"));
}

template<class R, class... Args, std::size_t... Is>
R callFunction(R (*f)(Args...), object::argsContainer& args, std::index_sequence<Is...>)
{
    if (isTrue((args[Is]->getValue().type().hash_code() == typeid(typename guessType<Args>::type).hash_code())...))
        return f((typeConverter<Args, typename guessType<Args>::type>(*std::any_cast<typename guessType<Args>::type>(&args[Is]->getValue())))...);
    throw(WrongTypeOfArgument("Wrong type of argument"));
}


template<class O, class M, M f, class R, class... Args>
std::enable_if_t<std::is_same<R, void>::value, object::objectPtr> method (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() != sizeof...(Args))
        throw(WrongNumberOfArguments("Wrong number of arguments"));
    callMethod(std::any_cast<O>(&obj->getParent()->getValue()), f, args, std::index_sequence_for<Args...>());
    return obj->getParent();
}

template<class O, class M, M f, class R, class... Args>
std::enable_if_t<!std::is_same<R, void>::value, object::objectPtr> method (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() != sizeof...(Args))
        throw(WrongNumberOfArguments("Wrong number of arguments"));
    if (std::is_convertible<typename resultOf<M>::type, R>::value)
        return obj->READ(guessTypeName<R>::name, true)->CALL()->setValue((R) callMethod(std::any_cast<O>(&obj->getParent()->getValue()), f, args, std::index_sequence_for<Args...>()));
    else
        return obj->READ(guessTypeName<R>::name, true)->CALL()->setValue(typeConverter<R, typename resultOf<M>::type>(callMethod(std::any_cast<O>(&obj->getParent()->getValue()), f, args, std::index_sequence_for<Args...>())));
}

template<class F, F f, class R,  class... Args>
std::enable_if_t<std::is_same<R, void>::value, object::objectPtr> function (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() != sizeof...(Args))
        throw(WrongNumberOfArguments("Wrong number of arguments"));
    callFunction(f, args, std::index_sequence_for<Args...>());
    return obj->getParent();
}

template<class F, F f, class R,  class... Args>
std::enable_if_t<!std::is_same<R, void>::value, object::objectPtr> function (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() != sizeof...(Args))
        throw(WrongNumberOfArguments("Wrong number of arguments"));
    if (std::is_convertible<typename resultOf<F>::type, R>::value)
        return obj->READ(guessTypeName<R>::name, true)->CALL()->setValue((R) callFunction(f, args, std::index_sequence_for<Args...>()));
    else
        return obj->READ(guessTypeName<R>::name, true)->CALL()->setValue(typeConverter<R, typename resultOf<F>::type>(callFunction(f, args, std::index_sequence_for<Args...>())));
}

object::objectPtr wrongNumberOfArguments (object::objectPtr obj, object::argsContainer& args);

template<object::nativeFunctionType... F>
object::objectPtr functionChooser (object::objectPtr obj, object::argsContainer& args)
{
    object::nativeFunctionType functions[sizeof...(F)] = {F...};
    if (args.size() < sizeof...(F))
        return functions[args.size()](obj, args);
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

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