#ifndef JUSTINTIMEC_H_
#define JUSTINTIMEC_H_

#include <string>
#include <cstddef>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <libtcc.h>
#include "interface.h"
#include "osDependent.h"

namespace jit
{
class function
{
public:
    using functionType = object::objectRawPtr(*)(object::objectRawPtr, object::objectRawPtr*, int);
    function(const std::string& name, const std::string& body) : s(nullptr), functionPointer(nullptr)
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

        buffer.resize(tcc_relocate(s, nullptr));

        if (tcc_relocate(s, reinterpret_cast<void*>(&buffer.front())) < 0)
        {
            std::cerr << "tcc_relocate failed" << std::endl;
            return;
        }

        functionPointer = reinterpret_cast<functionType>(tcc_get_symbol(s, name.c_str()));
    }
    ~function()
    {
        if (s) tcc_delete(s);
    }

    object::objectPtr operator()(object::objectPtr obj, object::arrayType& args)
    {
        if (!functionPointer) return nullptr;
        std::vector<object::objectRawPtr> argsRaw(args.size()); 
        std::transform(args.begin(), args.end(), argsRaw.begin(), [](object::objectPtr& a) -> object::objectRawPtr { return a.get(); });
        return functionPointer(obj.get(), &argsRaw.front(), argsRaw.size())->shared_from_this();
    }

private:
    TCCState *s;
    functionType functionPointer;
    std::vector<std::byte> buffer;
};
    
}

#endif
