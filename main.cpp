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
class x
{
    public:
    void foo(int a, float b)
    {
      std::cout << (a*10+b) << std::endl;
      c = (a*10+b);
    }
    int c = 0;
};

void print(int x)
{
    std::cout<<x<<std::endl;
}

void print(int x, float y)
{
    std::cout<<x<<" "<<y<<std::endl;
}

int main(int argc, char** argv)
{

    name::initialize();
    std::pair<object::objectPtr, object::objectPtr> RootWithFather = prepareTree();

    x result;


    object::objectPtr xobj = RootWithFather.second->READ(name("Object"))->CALL()->setValue(result);

    //template<class S, S f, class R, const char* typeName,  class... Args>
    xobj->addChild(std::make_shared<object>(FunctionChooser<
                                            WrongNumberOfArguments,
                                            VFunction<void (*)(int), print, int>,
                                            VFunction<void (*)(int, float), print, int, float>
                                            >, name("Function")));

    argsContainer ar;
    ar.push_back(std::make_shared<object>(1));
    xobj->READ(name("Function"))->CALL(ar);
    ar.push_back(std::make_shared<object>(1.2f));
    xobj->READ(name("Function"))->CALL(ar);

    xobj->addChild(std::make_shared<object>(VMethod<x, void (x::*)(int,float), &x::foo, int, float>, name("Method")));
    xobj->READ(name("Method"))->CALL(ar);



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
