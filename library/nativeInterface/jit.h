#ifndef JUSTINTIMEC_H_
#define JUSTINTIMEC_H_

#include <string>
//#include <cstddef>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <stdexcept>
#include <libtcc.h>
#include "interface.h"
#include "osDependent.h"

namespace jit
{
class interface
{
public:
    using functionType = object::objectRawPtr(*)(object::objectRawPtr, object::objectRawPtr*, int);
    void addLibs(const std::filesystem::path& path)
    {
        tcc_add_library_path(s, path.string().c_str());
        for (const std::filesystem::directory_entry& p : std::filesystem::directory_iterator(path))
        {
            #ifdef _WIN32
            if (p.path().extension().string() == ".def")
                tcc_add_library(s, p.path().stem().string().c_str());
            #else
            if (p.path().extension().string() == ".a")
                tcc_add_file(s, p.path().string().c_str());
            if (p.path().extension().string() == ".so")
                tcc_add_file(s, p.path().string().c_str());
            if (p.path().extension().string() == ".o")
                tcc_add_file(s, p.path().c_str());
            #endif
            if (std::filesystem::is_directory(p.path()))
                addLibs(p.path());
        }
    }
    interface(const std::string& body) : s(nullptr)
    {
        s = tcc_new();
        if (!s)
        {
            throw(std::runtime_error("tcc_new failed"));
        }

        tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

        addLibs(std::filesystem::path(getExecutablePath()).parent_path()/std::filesystem::path("lib"));


        tcc_set_lib_path(s, (std::filesystem::path(getExecutablePath()).parent_path()/std::filesystem::path("lib")).string().c_str());
        tcc_add_include_path(s, (std::filesystem::path(getExecutablePath()).parent_path()/std::filesystem::path("include")).string().c_str());

        tcc_define_symbol(s, "INTERFACE", nullptr);

        if (tcc_compile_string(s, body.c_str()) == -1)
        {
            throw(std::runtime_error("tcc_compile_string failed"));
        }

        tcc_add_symbol(s, "getInt", (void*)getInt);
        tcc_add_symbol(s, "setInt", (void*)setInt);
        tcc_add_symbol(s, "getDouble", (void*)getDouble);
        tcc_add_symbol(s, "setDouble", (void*)setDouble);
        tcc_add_symbol(s, "getString", (void*)getString);
        tcc_add_symbol(s, "setString", (void*)setString);
        tcc_add_symbol(s, "getVoidPtr", (void*)getVoidPtr);
        tcc_add_symbol(s, "setVoidPtr", (void*)setVoidPtr);

        tcc_add_symbol(s, "readNormal", (void*)readNormal);
        tcc_add_symbol(s, "readRecursive", (void*)readRecursive);
        tcc_add_symbol(s, "var", (void*)var);
        object* (*c)(object*, ...) = call;
        tcc_add_symbol(s, "call", (void*)c);

        //buffer.resize(tcc_relocate(s, nullptr));
        //if (tcc_relocate(s, reinterpret_cast<void*>(&buffer.front())) < 0)
        if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0)
        {
            throw(std::runtime_error("tcc_relocate failed"));
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
