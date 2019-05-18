#ifndef JUSTINTIMEC_H_
#define JUSTINTIMEC_H_

#include <string>
//#include <cstddef>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <libtcc.h>
#include "interface.h"
#include "osDependent.h"

namespace jit
{
class interface
{
public:
    using functionType = object::objectRawPtr(*)(object::objectRawPtr, object::objectRawPtr*, int);
    interface(const std::string& body) : s(nullptr)
    {
        s = tcc_new();
        tcc_set_lib_path(s, (std::filesystem::path(getExecutablePath()).parent_path()/std::filesystem::path("lib")).string().c_str());
        if (!s)
        {
            std::cerr << "tcc_new failed" << std::endl;
            return;
        }
        tcc_add_library_path(s, (std::filesystem::path(getExecutablePath()).parent_path()/std::filesystem::path("lib")).string().c_str());
        tcc_add_include_path(s, (std::filesystem::path(getExecutablePath()).parent_path()/std::filesystem::path("include")).string().c_str());

        #ifdef _WIN32
        std::string libraryExtension = ".def";
        #else
        std::string libraryExtension = ".a";
        #endif

        for (const std::filesystem::directory_entry& p : std::filesystem::directory_iterator(
            std::filesystem::path(getExecutablePath()).parent_path()/std::filesystem::path("lib")
        ))
        {
            if (p.path().extension() == libraryExtension)
                tcc_add_library(s, p.path().stem().string().c_str());
        }

        tcc_define_symbol(s, "INTERFACE", nullptr);

        tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

        if (tcc_compile_string(s, body.c_str()) == -1)
        {
            std::cerr << "tcc_compile_string failed" << std::endl;
            return;
        }

        tcc_add_symbol(s, "getInt", (void*)getInt);
        tcc_add_symbol(s, "setInt", (void*)setInt);
        tcc_add_symbol(s, "getDouble", (void*)getDouble);
        tcc_add_symbol(s, "setDouble", (void*)setDouble);
        tcc_add_symbol(s, "getString", (void*)getString);
        tcc_add_symbol(s, "setString", (void*)setString);

        tcc_add_symbol(s, "ezRead", (void*)ezRead);
        tcc_add_symbol(s, "ezReadRecursive", (void*)ezReadRecursive);
        tcc_add_symbol(s, "ezVar", (void*)ezVar);
        object* (*c)(object*, ...) = ezCall;
        tcc_add_symbol(s, "ezCall", (void*)c);

        //buffer.resize(tcc_relocate(s, nullptr));
        //if (tcc_relocate(s, reinterpret_cast<void*>(&buffer.front())) < 0)
        if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0)
        {
            std::cerr << "tcc_relocate failed" << std::endl;
            return;
        }
    }
    ~interface()
    {
        if (s) tcc_delete(s);
    }
    functionType get(const std::string& name)
    {
        functionType res = reinterpret_cast<functionType>(tcc_get_symbol(s, name.c_str()));
        if (res == nullptr)
            throw(NotFound("Symbol ", name, " not found"));
        return res;
    }
    static object::objectPtr callFunction(functionType functionPointer, object::objectPtr obj, object::arrayType& args)
    {
        std::vector<object::objectRawPtr> argsRaw(args.size()); 
        std::transform(args.begin(), args.end(), argsRaw.begin(), [](object::objectPtr& a) -> object::objectRawPtr { return a.get(); });
        object::objectRawPtr ret = functionPointer(obj.get(), &argsRaw.front(), argsRaw.size());
        if (ret != nullptr)
            return ret->shared_from_this();
        else
            return obj;
    }
private:
    TCCState *s;
    //std::vector<std::byte> buffer;
    std::string toThrow;
};
    
}

#endif
