#include <cstring>
#include "interface.h"

int getInt(object::objectRawPtr a)
{
    int result = 0;
    try {
        result = std::any_cast<int>(a->getValue());
    }
    catch (const std::exception&) {
        throw(WrongTypeOfArgument("Argument is not int in getInt"));
    }
    return result;
}
void setInt(object::objectRawPtr a, int i)
{
    a->getValue() = i;
}

double getDouble(object::objectRawPtr a)
{
    double result = 0.0;
    try {
        result = std::any_cast<double>(a->getValue());
    }
    catch (const std::exception&) {
        throw(WrongTypeOfArgument("Argument is not double in getDouble"));
    }
    return result;
}
void setDouble(object::objectRawPtr a, double d)
{
    a->getValue() = d;
}

const char* getString(object::objectRawPtr a)
{
    const char* result = nullptr;
    try {
        if (a->getValue().type().hash_code() != typeid(std::string).hash_code())
            throw(std::runtime_error("Wrong type"));
        result = std::any_cast<std::string>(&a->getValue())->c_str();
    }
    catch (const std::exception&) {
        throw(WrongTypeOfArgument("Argument is not string in getString"));
    }
    return result;
}
void setString(object::objectRawPtr a, const char* s)
{
    a->getValue() = std::string(s);
}

void* getVoidPtr(object::objectRawPtr a)
{
    void* result = nullptr;
    try {
        result = std::any_cast<void*>(a->getValue());
    }
    catch (const std::exception&) {
        throw(WrongTypeOfArgument("Argument is not void* in getVoidPtr"));
    }
    return result;
}
void setVoidPtr(object::objectRawPtr a, void* v)
{
    a->getValue() = v;
}

object::objectRawPtr readNormal(object::objectRawPtr obj, const char* name)
{
    return obj->READ(std::string(name)).get();
}

object::objectRawPtr readRecursive(object::objectRawPtr obj, const char* name)
{
    return obj->READ(std::string(name), true).get();
}

//TODO: fix "var" function
/*object::objectRawPtr var(object::objectRawPtr obj, const char* name)
{
    return obj->READ(std::string(name), true, object::forceCreateMode::var).get();
}*/

//TODO: fix "call" function
/*object::objectRawPtr call(object::objectRawPtr obj, ...)
{
    static object::arrayType orphanage;
    //object::objectPtr orphanage = obj->READ(name("Array"), true)->CALL()->setName("orphanage");
    //caller->addChild(orphanage);
    //->READ(name("pushBack"))->CALL();
    object::arrayType args;
    object::objectRawPtr next;

    orphanage.erase(std::remove_if(orphanage.begin(), orphanage.end(),
        [](const object::objectPtr& x) {
            return x->getRawParent(false) != nullptr;
        }), orphanage.end());

    va_list varags;
    va_start(varags, obj);
    while ((next = va_arg(varags, object::objectRawPtr)) != nullptr)
    {
        args.push_back(next->shared_from_this());
    }
    va_end(varags);

    //object::objectPtr res = obj->CALL(args);
    //object::getRoot()->READ(name("orphanage"))->READ(name("pushBack"))->CALL((res = obj->CALL(args).get())->shared_from_this());
    //orphanage.push_back(res);
    //object::callStack.private_push(res);
    //object::callStack.trace();
    //return res.get();
    orphanage.push_back(obj->CALL(args));
    return orphanage.back().get();
}*/
