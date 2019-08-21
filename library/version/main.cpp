#include <string>
#include "nobject.h"
#include "SHA1.h"

#if defined(__GNUC__)
# if defined(__GNUC_PATCHLEVEL__)
#  define __GNUC_VERSION__ (__GNUC__ * 10000 \
                            + __GNUC_MINOR__ * 100 \
                            + __GNUC_PATCHLEVEL__)
# else
#  define __GNUC_VERSION__ (__GNUC__ * 10000 \
                            + __GNUC_MINOR__ * 100)
# endif
#endif

object::objectPtr initVersion (object::objectPtr obj, object::arrayType& args)
{
    std::string compilerVersion;
    #ifdef _MSC_VER
        compilerVersion = std::to_string(_MSC_VER);
    #elif __GNUC_VERSION__
        compilerVersion = std::to_string(__GNUC_VERSION__);
    #endif

    obj->addChild(constructObject(obj, "String", std::string(__DATE__))->setName(name("compilationDate")))
       ->addChild(constructObject(obj, "String", std::string(__TIME__))->setName(name("compilationTime")))
       ->addChild(constructObject(obj, "String", compilerVersion)->setName(name("compilerVersion")))
       ->addChild(constructObject(obj, "String", std::string(GIT_SHA1))->setName(name("gitSHA1")));

    return nullptr;
}
