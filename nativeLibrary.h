#ifndef NATIVELIBRARY_H_
#define NATIVELIBRARY_H_

#include "nobject.h"

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

extern "C"
{
    EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::arrayType& args);
}

namespace nativeLibrary
{
    void initialize(object::objectPtr& obj, object::arrayType& args)
    {
        name::initialize(std::any_cast<name::initializationPack>(args[0]->getValue()));
        asyncTasks::initialize(std::any_cast<asyncTasks::sharedStaticMembers>(args[1]->getValue()));
        object::initialize(obj->READ(name("Root"), true));
    }
}


#endif
