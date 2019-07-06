//cmake .
//cmake --build . --config Release

//#define DEBUG

#if defined(DEBUG)
#pragma message ("Debug mode on")
#endif
#include "prepareTree.h"
#include "osDependent.h"
#include <string>

inline bool isFlag(const char* input, const char* flag)
{
    return std::strcmp(input, flag) == 0 || (std::strcmp(input + 1, flag) == 0 && input[0] == '-');
}

int main(int argc, char** argv)
{
    int returnCode = 0;
    try
    {
        initialize();
        prepareTree();
        try
        {
            std::string entryPoint;
            std::vector<std::string> fileNames;
            object::arrayType args;
            for (int i = 0; i < argc; i++)
            {
                if (isFlag(argv[i], "-file") && i != argc-1)
                {
                    fileNames.push_back(std::string(argv[++i]));
                }
                else if (isFlag(argv[i], "-entryPoint") && i != argc-1)
                {
                    entryPoint = argv[++i];
                }
                else if (isFlag(argv[i], "-help"))
                {
                    IO::console << "See project's repository (there are tutorial and language reference): https://github.com/Antollo/Easypt\n";
                }
                else
                {
                    args.push_back(object::getRawRoot()->READ(name("String"))->CALL()->setValue(std::string(argv[i])));
                    //object::getRawRoot()->READ(name("launchArgs"))->READ(name("pushBack"))->CALL(object::getRawRoot()->READ(name("String"))->CALL()->setValue(std::string(argv[i]))->setName("arg"));
                }
            }

            for(auto& fileName : fileNames)
            {
                object::objectPtr sourceBlockCallable = object::getRawRoot()->READ(name("import"))->CALL(object::getRawRoot()->READ(name("String"))->CALL()->setValue(fileName));
            }

            object::objectPtr entryPointString = object::getRawRoot()->READ(name("String"))->CALL();
            entryPointString->getValue() = entryPoint;
            object::objectPtr entryPointBlockCallable = object::getRawRoot()->READ(name("parse"))->CALL(entryPointString);
            entryPointBlockCallable->setName("EntryPointBlockCallable");
            object::objectPtr returnCodeObject = entryPointBlockCallable->CALL(args);
            if (returnCodeObject->hasSignature(name("Int")))
                returnCode = std::any_cast<int>(returnCodeObject->getValue());
        }
        catch (std::exception& e)
        {
            auto arr = getExceptionsArray(e);
            errorOut(arr);
        }
        //asyncTasks::unregisterThisThread();
        bool released = false;
        while (!released)
        {
            try
            {
                object::release();
                released = true;
            }
            catch(std::exception& e)
            {
                auto arr = getExceptionsArray(e);
                errorOut(arr);
            }
            
        }
    }
    catch(...)
    {
        errorOut("Fatal error occurred.");
    }
    return returnCode;
}
