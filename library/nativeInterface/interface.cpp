#include <cstring>
#include "interface.h"

int getInt(object::objectRawPtr a)
{
    int result = 0;
    try {
        result = *std::any_cast<int>(&a->getValue());
    }
    catch(const std::bad_any_cast& e) {
        std::cerr << e.what() << std::endl;
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
        result = *std::any_cast<double>(&a->getValue());
    }
    catch(const std::bad_any_cast& e) {
        std::cerr << e.what() << std::endl;
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
        result = std::any_cast<std::string>(&a->getValue())->c_str();
    }
    catch(const std::bad_any_cast& e) {
        std::cerr << e.what() << std::endl;
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
        result = *std::any_cast<void*>(&a->getValue());
    }
    catch(const std::bad_any_cast& e) {
        std::cerr << e.what() << std::endl;
    }
    return result;
}
void setVoidPtr(object::objectRawPtr a, void* v)
{
    a->getValue() = v;
}