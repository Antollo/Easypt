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
    initialize();
    std::pair<object::objectPtr, object::objectPtr> RootWithFather = prepareTree();
    std::string source, entryPoint;
    std::list<std::string> fileNames;
    for(int i=0; i<argc; i++)
    {
        if (isFlag(argv[i], "-file") && i != argc-1)
        {
            fileNames.push_back(std::string(argv[++i]));
            std::ifstream sourceFile(argv[i]);
            std::getline(sourceFile, source, (char)EOF);
            sourceFile.close();
        }
        else if (isFlag(argv[i], "-entryPoint") && i != argc-1)
        {
            entryPoint = argv[++i];
        }
        else if (isFlag(argv[i], "-help"))
        {
            IO::basicOut<<"See project's repository (there are tutorial and language reference): https://github.com/Antollo/Easypt";
        }
        else
        {
            RootWithFather.second->READ(name("launchArgs"))->READ(name("pushBack"))->CALL(RootWithFather.second->READ(name("String"))->CALL()->setValue(std::string(argv[i]))->setName("arg"));
        }
    }
    try
    {
        for(auto& fileName : fileNames)
        {
            object::objectPtr sourceBlockCallable = RootWithFather.second->READ(name("import"))->CALL(RootWithFather.second->READ(name("String"))->CALL()->setValue(fileName));
        }

        object::objectPtr entryPointString = RootWithFather.second->READ(name("String"))->CALL();
        entryPointString->getValue() = entryPoint;
        object::objectPtr entryPointBlockCallable = RootWithFather.second->READ(name("parse"))->CALL(entryPointString);
        //TODO BlockCallable should change its name itself
        entryPointBlockCallable->getName() = "EntryPointBlockCallable";
        entryPointBlockCallable->CALL();
    }
    catch (exception& e)
    {
        RootWithFather.second->READ(name("basicOut"))->CALL(constructObject(RootWithFather.second, "String", e.getMessage()));
    }
    catch (std::exception& e)
    {
        RootWithFather.second->READ(name("basicOut"))->CALL(constructObject(RootWithFather.second, "String", "Unknown exception: " + std::string(e.what())));
    }
    catch (object::objectPtr& e)
    {
        RootWithFather.second->READ(name("basicOut"))->CALL(e);
    }
    object::release();
    return 0;
}
