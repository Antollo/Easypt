#include "osDependent.h"

std::string getExecutablePath()
{
    static std::string ret;
    if (!ret.empty()) return ret;
    #if defined(_WIN32)
        char result[MAX_PATH];
        ret = std::string(result, GetModuleFileName(NULL, result, MAX_PATH ));
    #elif defined(__linux__)
        char result[ PATH_MAX ];
        ssize_t length = readlink( "/proc/self/exe", result, PATH_MAX );
        ret = std::string( result, (length > 0) ? length : 0 );
    #else
        return "";
    #endif
    return ret;
}

dynamicLibrary::dynamicLibrary()
{
    #if defined(_WIN32)
        library = 0;
    #elif defined(__linux__)
        library = 0;
    #else
        throw(NotSupportedOnThisOS("Dynamic libraries are not supported on this OS"))
    #endif
}
inline size_t findLastSlash(const std::string& str)
{
    return std::min(str.find_last_of('\\'), str.find_last_of('/'));
}
void dynamicLibrary::loadLibrary(const std::string& fileName)
{
    #if defined(_WIN32)
        library = LoadLibraryA((fileName + ".dll").c_str());
        if (!library)
        {
            std::string executablePath = getExecutablePath();
            library = LoadLibraryA((executablePath.substr(0, findLastSlash(executablePath) + 1) + fileName + ".dll").c_str());
            if (!library) throw(FileNotFound("Library ", fileName, " not found"));
        }
    #elif defined(__linux__)
        library = dlopen(("./lib" + fileName + ".so").c_str(), RTLD_LAZY);
        if (!library)
        {
            std::string executablePath = getExecutablePath();
            library = dlopen((executablePath.substr(0, findLastSlash(executablePath) + 1) + "lib" + fileName + ".so").c_str(), RTLD_LAZY);
            if (!library) throw(FileNotFound("Library ", fileName, " not found"));
        }
    #else
        library = false;
        throw(NotSupportedOnThisOS("Dynamic libraries are not supported on this OS"))
    #endif
}
object::nativeFunctionType dynamicLibrary::getFunction(const std::string& functionName)
{
	if (!library) return nullptr;
    #if defined(_WIN32)
        object::nativeFunctionType function = reinterpret_cast<object::nativeFunctionType>(GetProcAddress(library, functionName.c_str()));
        if (!function) throw(NotFound("Function ", functionName, " not found"));
        return function;
    #elif defined(__linux__)
        object::nativeFunctionType function = reinterpret_cast<object::nativeFunctionType>(dlsym(library, functionName.c_str()));
        if (!function) throw(NotFound("Function ", functionName, " not found"));
        return function;
    #else
        throw(NotSupportedOnThisOS("Dynamic libraries are not supported on this OS"))
    #endif
}
dynamicLibrary::~dynamicLibrary()
{
    #if defined(_WIN32)
    if (library)
    {
        FreeLibrary(library);
		library = nullptr;
    }
    #elif defined(__linux__)
    if (library)
    {
        dlclose(library);
		library = nullptr;
    }
    #else
        throw(NotSupportedOnThisOS("Dynamic libraries are not supported on this OS"))
    #endif
}

void initialize()
{
    std::ios_base::sync_with_stdio(false);
    std::cout << std::boolalpha;
    name::initialize();
    #if defined(_WIN32)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return;
    }
    #endif
}