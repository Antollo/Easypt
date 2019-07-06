#ifdef _WIN32
    #define _CRT_SECURE_NO_WARNINGS
#endif
#include <cstdlib>
#include <sstream>
#include <cctype>
#include "nobject.h"
#include "nativeLibrary.h"

#ifdef _WIN32
    #include "windows.h"
// Adapted from https://stackoverflow.com/a/35658917
std::string shellInterfaceImpl(const std::string& cmd)
{
    std::stringstream outStream;
    HANDLE hPipeRead, hPipeWrite, hInPipeRead, hInPipeWrite;

    SECURITY_ATTRIBUTES saAttr = {sizeof(SECURITY_ATTRIBUTES)};
    saAttr.bInheritHandle = TRUE; // Pipe handles are inherited by child process.
    saAttr.lpSecurityDescriptor = NULL;

    // Create a pipe to get results from child's stdout.
    if (!CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0))
        throw(Unknown("shellInterfaceImpl error"));

    if (!CreatePipe(&hInPipeRead, &hInPipeWrite, &saAttr, 0))
        throw(Unknown("shellInterfaceImpl error"));

    STARTUPINFOW si = {sizeof(STARTUPINFOW)};
    si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.hStdOutput  = hPipeWrite;
    si.hStdError   = hPipeWrite;
    si.hStdInput   = hInPipeRead;
    si.wShowWindow = SW_HIDE; // Prevents cmd window from flashing.
                              // Requires STARTF_USESHOWWINDOW in dwFlags.

    PROCESS_INFORMATION pi = { 0 };

    std::wstring lpCommandLine = L"powershell -nologo";
    BOOL fSuccess = CreateProcessW(NULL, (LPWSTR)lpCommandLine.c_str(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

    if (! fSuccess)
    {
        CloseHandle(hPipeWrite);
        CloseHandle(hPipeRead);
        CloseHandle(hInPipeWrite);
        CloseHandle(hInPipeRead);
        throw(Unknown("shellInterfaceImpl error, check if following path is valid: C:\\WINDOWS\\system32\\WindowsPowerShell\\v1.0\\PowerShell.exe"));
    }

    BOOL bSuccess = FALSE;
    DWORD dwWritten;

    std::string temp = "function prompt { \"<PS_PROMPT_TOKEN>\" }\n";
    bSuccess = WriteFile(hInPipeWrite, temp.c_str(), temp.size(), &dwWritten, NULL);
    if (! bSuccess )
        throw(Unknown("shellInterpfaceImpl error"));

    bSuccess = WriteFile(hInPipeWrite, cmd.c_str(), cmd.size(), &dwWritten, NULL);
    if (! bSuccess )
        throw(Unknown("shellInterpfaceImpl error"));
    
    temp = "\nexit\n";
    bSuccess = WriteFile(hInPipeWrite, temp.c_str(), temp.size(), &dwWritten, NULL);
    if (! bSuccess )
        throw(Unknown("shellInterpfaceImpl error"));
 
    CloseHandle(hInPipeWrite);

    bool bProcessEnded = false;
    while (!bProcessEnded)
    {
        // Give some timeslice (50 ms), so we won't waste 100% CPU.
        bProcessEnded = WaitForSingleObject( pi.hProcess, 50) == WAIT_OBJECT_0;

        // Even if process exited - we continue reading, if
        // there is some data available over pipe.
        while (true)
        {
            char buf[1024];
            DWORD dwRead = 0;
            DWORD dwAvail = 0;

            if (!::PeekNamedPipe(hPipeRead, NULL, 0, NULL, &dwAvail, NULL))
                break;

            if (!dwAvail) // No data available, return
                break;

            if (!::ReadFile(hPipeRead, buf, min(sizeof(buf) - 1, dwAvail), &dwRead, NULL) || !dwRead)
                // Error, the child process might ended
                break;

            buf[dwRead] = 0;
            //std::cout<<buf;
            outStream << buf;
        }
    }

    CloseHandle(hPipeWrite);
    CloseHandle(hPipeRead);
    CloseHandle(hInPipeRead);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::string res;
    std::size_t c = 0;
    while (std::getline(outStream, temp, '\n'))
    {
        c++;
        if (c == 1) continue;
        if (std::all_of(temp.begin(), temp.end(), std::isspace)) continue;
        if (temp.find("<PS_PROMPT_TOKEN>") == 0) continue;
        res += temp;
        if (res.back() == '\r') res.back() = '\n';
        else if (outStream.peek() == '\n') res += "\n";
    }
    if (res.back() == '\n') res.pop_back();
    return res;
}
#else
std::string shellInterfaceImpl(const std::string& cmd)
{
    std::string res;
    std::array<char, 128> buffer;
	std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe)
	{
		throw(Unknown("shellInterpfaceImpl error"));
	}
	while (!feof(pipe.get()))
	{
		if (fgets(buffer.data(), 128, pipe.get()) != NULL)
		{
			res += buffer.data();
		}
	}
    return res;
}
#endif

object::objectPtr callShellCommand (object::objectPtr obj, object::arrayType& args)
{
    std::string command;
    for (auto& arg : args)
    {
        if (arg->hasSignature(name("String")))
        {
            command += *std::any_cast<std::string>(&arg->getValue());
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
        }
    }
    std::system(command.c_str());
    return obj->getParent();
}

object::objectPtr shellInterface (object::objectPtr obj, object::arrayType& args)
{
    std::string command, token;
    if (args.size() >= 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            command = *std::any_cast<std::string>(&args[0]->getValue());
            for (std::size_t i = 1; i< args.size(); i++)
            {
                token = "${" + std::to_string(i) + "}";
                while (command.find(token) != std::string::npos)
                    command.replace(command.find(token), token.size(), std::any_cast<std::string>(args[i]->READ("toString")->CALL()->getValue()));
            }
            return constructObject(obj, "String", shellInterfaceImpl(command));
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

object::objectPtr getEnvironmentVariable (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        if (args[0]->hasSignature(name("String")))
        {
            char* res = std::getenv(std::any_cast<std::string>(&args[0]->getValue())->c_str());
            return constructObject(obj, "String", std::string((res == nullptr) ? "" : res));
        }
        else
        {
            throw(WrongTypeOfArgument("Argument is not String in ", obj->getFullNameString()));
        }
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::arrayType& args)
{
    nativeLibrary::initialize(obj, args);

    std::string osName = "";
    #if defined(_WIN32)
        osName = "windows";
    #elif defined(__linux__)
        osName = "linux";
    #endif

    obj->addChild(makeObject(callShellCommand, name("callShellCommand")))
        ->addChild(makeObject(shellInterface, name("shellInterface")))
        ->addChild(makeObject(getEnvironmentVariable, name("getEnvironmentVariable")))
        ->addChild(constructObject(obj, "String", osName)->setName(name("osName")));
    return nullptr;
}
