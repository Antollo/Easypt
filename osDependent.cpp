#include "osDependent.h"

std::string getExecutablePath()
{
    static std::string ret;
    if (!ret.empty()) return ret;
    #if defined(_WIN32)
        char result[MAX_PATH];
        ret = std::string(result, GetModuleFileName(NULL, result, MAX_PATH ));
    #elif defined(__linux__)
        char result[PATH_MAX];
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

#if defined(_WIN32)
void translateSEH(unsigned int u, EXCEPTION_POINTERS* exceptionPtr)
{
    std::string name = [&u](){
        switch(u) {
            case EXCEPTION_ACCESS_VIOLATION:            return "EXCEPTION_ACCESS_VIOLATION"         ;
            case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:       return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED"    ;
            case EXCEPTION_BREAKPOINT:                  return "EXCEPTION_BREAKPOINT"               ;
            case EXCEPTION_DATATYPE_MISALIGNMENT:       return "EXCEPTION_DATATYPE_MISALIGNMENT"    ;
            case EXCEPTION_FLT_DENORMAL_OPERAND:        return "EXCEPTION_FLT_DENORMAL_OPERAND"     ;
            case EXCEPTION_FLT_DIVIDE_BY_ZERO:          return "EXCEPTION_FLT_DIVIDE_BY_ZERO"       ;
            case EXCEPTION_FLT_INEXACT_RESULT:          return "EXCEPTION_FLT_INEXACT_RESULT"       ;
            case EXCEPTION_FLT_INVALID_OPERATION:       return "EXCEPTION_FLT_INVALID_OPERATION"    ;
            case EXCEPTION_FLT_OVERFLOW:                return "EXCEPTION_FLT_OVERFLOW"             ;
            case EXCEPTION_FLT_STACK_CHECK:             return "EXCEPTION_FLT_STACK_CHECK"          ;
            case EXCEPTION_FLT_UNDERFLOW:               return "EXCEPTION_FLT_UNDERFLOW"            ;
            case EXCEPTION_ILLEGAL_INSTRUCTION:         return "EXCEPTION_ILLEGAL_INSTRUCTION"      ;
            case EXCEPTION_IN_PAGE_ERROR:               return "EXCEPTION_IN_PAGE_ERROR"            ;
            case EXCEPTION_INT_DIVIDE_BY_ZERO:          return "EXCEPTION_INT_DIVIDE_BY_ZERO"       ;
            case EXCEPTION_INT_OVERFLOW:                return "EXCEPTION_INT_OVERFLOW"             ;
            case EXCEPTION_INVALID_DISPOSITION:         return "EXCEPTION_INVALID_DISPOSITION"      ;
            case EXCEPTION_NONCONTINUABLE_EXCEPTION:    return "EXCEPTION_NONCONTINUABLE_EXCEPTION" ;
            case EXCEPTION_PRIV_INSTRUCTION:            return "EXCEPTION_PRIV_INSTRUCTION"         ;
            case EXCEPTION_SINGLE_STEP:                 return "EXCEPTION_SINGLE_STEP"              ;
            case EXCEPTION_STACK_OVERFLOW:              _resetstkoflw();
                                                        return "EXCEPTION_STACK_OVERFLOW"           ;
            default: return "UNKNOWN EXCEPTION" ;
       }
    }();
    throw Unknown("Win32 exception " + name);
}
#endif

void initialize()
{
    //std::ios_base::sync_with_stdio(false);
    std::cout << std::boolalpha;
    name::initialize();
    asyncTasks::initialize(std::make_shared<asyncTasks::staticMembers>());
    asyncTasks::registerThisThread();
    #if defined(_WIN32)
    _set_se_translator(translateSEH);
    ULONG_PTR lowLimit;
    ULONG_PTR highLimit;
    GetCurrentThreadStackLimits(&lowLimit, &highLimit);
    static ULONG size = (highLimit - lowLimit)/8*7;
    SetThreadStackGuarantee(&size);
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