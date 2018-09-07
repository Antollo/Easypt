#include "prepareTree.h"
//cmake .
//cmake --build . --config Release

//#define DEBUG

#if defined(DEBUG)
#pragma message ("Debug mode on")
#endif
#include "prepareTree.h"
#include <fstream>
#include <string>

int main(int argc, char** argv)
{

    name::initialize();
    std::pair<object::objectPtr, object::objectPtr> RootWithFather = prepareTree();
    std::string source, entryPoint;
    for(int i=0; i<argc; i++)
    {
        if (std::strcmp(argv[i], "-file") == 0 && i != argc-1)
        {
            std::ifstream sourceFile(argv[++i]);
            std::getline(sourceFile, source, (char)EOF);
            sourceFile.close();
        }
        else if (std::strcmp(argv[i], "-entryPoint") == 0 && i != argc-1)
        {
            entryPoint = argv[++i];
        }
        else
        {
            RootWithFather.second->READ(name("launchArgs"))->READ(name("pushBack"))->CALL(RootWithFather.second->READ(name("String"))->CALL()->setValue(std::string(argv[i]))->setName("arg"));
        }
    }
    try
    {
        object::objectPtr sourceString = RootWithFather.second->READ(name("String"))->CALL();
        sourceString->getValue() = source;
        object::objectPtr sourceBlockCallable = RootWithFather.second->READ(name("parse"))->CALL(sourceString);
        //TODO BlockCallable should change its name itself
        sourceBlockCallable->getName() = "SourceBlockCallable";
        sourceBlockCallable->CALL();

        object::objectPtr entryPointString = RootWithFather.second->READ(name("String"))->CALL();
        entryPointString->getValue() = entryPoint;
        object::objectPtr entryPointBlockCallable = RootWithFather.second->READ(name("parse"))->CALL(entryPointString);
        //TODO BlockCallable should change its name itself
        entryPointBlockCallable->getName() = "EntryPointBlockCallable";
        entryPointBlockCallable->CALL();
    }
    catch (exception& e)
    {
        RootWithFather.second->READ(name("errorOut"))->CALL(std::make_shared<object>(std::string(e.what()), name("exception")));
    }
    catch (std::exception& e)
    {
        RootWithFather.second->READ(name("errorOut"))->CALL(std::make_shared<object>("Unknown exception: " + std::string(e.what()), name("exception")));
    }
    object::release();
    return 0;
}
