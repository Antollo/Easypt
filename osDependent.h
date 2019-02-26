#ifndef OSDEPENDENT_H
#define OSDEPENDENT_H

#include "nobject.h"
#include "exception.h"
#include <string>
#include <algorithm>

#if defined(_WIN32)
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    using libraryType = HMODULE;
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#elif defined(__linux__)
    #include <cstdio>
    #include <sys/types.h>
    #include <unistd.h>
    #include <linux/limits.h>
    #include <dlfcn.h>
    using libraryType = void*;
#else
    #pragma message ("OS not fully supported")
    using libraryType = bool;
#endif

std::string getExecutablePath();

class dynamicLibrary
{
public:
    dynamicLibrary();
    void loadLibrary(const std::string& fileName);
    object::nativeFunctionType getFunction(const std::string& functionName);
    ~dynamicLibrary();
private:
    libraryType library;
};

void initialize();

#endif // OSDEPENDENT_H