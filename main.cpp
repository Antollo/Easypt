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
        if (std::strcmp(argv[i], "-entryPoint") == 0 && i != argc-1)
        {
            entryPoint = argv[++i];
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

        //x->debugTree(0);
        //object::objectPtr a = RootWithFather.first->READ(name("Root"))->READ(name("xyz"))->READCALL(RootWithFather.first->READ(name("Root"))->READ(name("1")))->debugTree(0);
        //RootWithFather.first->debugTree(0);
        //object::objectPtr a = RootWithFather.first->READ(name("Root"))->READ(name("String"))->CALL();
        //a->getValue() = std::string("100000");
        //a->READ(name("toInt"))->CALL();
        //RootWithFather.first->READ(name("Root"))->READ(name("String"))->CALL()->debugTree(0);
        //RootWithFather.first->debugTree(0);//READ(name("Root"))->CALL()->READ(name("="))->CALL()->END();
        //object::objectPtr lol = std::make_shared<object>(std::string("lol"), name("lol"));
        //lol->READ(name("Root"), true);
        //std::cout<< (*(Root->READ(name("Null"))->CALL()) == *(Root->READ(name("Null"))->CALL()));
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
