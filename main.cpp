#include "prepareTree.h"
//cmake .
//cmake --build . --config Release

//#define DEBUG

#if defined(DEBUG)
#pragma message ("Debug mode on")
#endif
#include "prepareTree.h"
#include <string>

int main(int argc, char** argv)
{

    name::initialize();
    std::pair<object::objectPtr, object::objectPtr> RootWithFather = prepareTree();
    std::string source, entryPoint;
    std::list<std::string> fileNames;
    for(int i=0; i<argc; i++)
    {
        if (std::strcmp(argv[i], "--file") == 0 && i != argc-1)
        {
            fileNames.push_back(std::string(argv[++i]));
            std::ifstream sourceFile(argv[i]);
            std::getline(sourceFile, source, (char)EOF);
            sourceFile.close();
        }
        else if (std::strcmp(argv[i], "--entryPoint") == 0 && i != argc-1)
        {
            entryPoint = argv[++i];
        }
        else if (std::strcmp(argv[i], "--help") == 0 && i != argc-1)
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
