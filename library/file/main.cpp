#include <fstream>
#include <memory>
#include "nobject.h"
#include "Common.h"

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

extern "C"
{
    EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args);
}

class file
{
public:
    file() : f(std::make_shared<std::fstream>()) {}
    file(const file& anotherFile) : f(anotherFile.f) {}
    void open(std::string name);
    void clear();
    void write(int x);
    void write(double x);
    void write(bool x);
    void write(std::string x);
    std::string read();
    std::string readAll();
private:
    std::shared_ptr<std::fstream> f;
    std::string fileName;
};

void file::open(std::string name)
{
    if (f->is_open()) f->close();
    f->open(name, std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    fileName = name;
    if (!f->good())
    {
        f->close();
        f->open(fileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
        if (!f->good())
            throw(FileNotFound("Error occurred while opening ", name));
    }
}

void file::clear()
{
    f->close();
    f->open(fileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    if (!f->good())
        throw(FileNotFound("Error occurred while opening ", fileName));
}

void file::write(int x)
{
    *f << x;
    f->flush();
    f->seekg(0, std::ios::beg);
}

void file::write(double x)
{
    *f << x;
    f->flush();
    f->seekg(0, std::ios::beg);
}

void file::write(bool x)
{
    *f << x;
    f->flush();
    f->seekg(0, std::ios::beg);
}

void file::write(std::string x)
{
    *f << x;
    f->flush();
    f->seekg(0, std::ios::beg);
}

std::string file::read()
{
    std::string temp;
    *f >> temp;
    //f->flush();
    //f->seekp(0, std::ios::end);
    f->clear();
    return temp;
}

std::string file::readAll()
{
    std::streampos p = f->tellg();
    f->seekg(0, std::ios::beg);
    std::string temp((std::istreambuf_iterator<char>(*f)), std::istreambuf_iterator<char>());
    f->seekg(p);
    return temp;
}

object::objectPtr File (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
    ret->getValue() = file();
    return ret;
};

object::objectPtr FileWrite (object::objectPtr obj, object::argsContainer& args)
{
    for(auto& arg : args)
    {
        if (arg->hasSignature(name("String")))
            std::any_cast<file>(&obj->getParent()->getValue())->write(*std::any_cast<std::string>(&arg->getValue()));
        else if (arg->hasSignature(name("Int")))
            std::any_cast<file>(&obj->getParent()->getValue())->write(*std::any_cast<int>(&arg->getValue()));
        else if (arg->hasSignature(name("Boolean")))
            std::any_cast<file>(&obj->getParent()->getValue())->write(*std::any_cast<bool>(&arg->getValue()));
        else if (arg->hasSignature(name("Double")))
            std::any_cast<file>(&obj->getParent()->getValue())->write(*std::any_cast<double>(&arg->getValue()));
        else if (arg->hasSignature(name("Basic")))
            std::any_cast<file>(&obj->getParent()->getValue())->write(*std::any_cast<std::string>(&(arg->READ(name("toString"))->CALL()->getValue())));
        else
            throw(WrongTypeOfArgument("Wrong type of argument while calling ", obj->getFullNameString()));
    };
    return obj->getParent();
};

EXPORT object::objectPtr exportLibrary (object::objectPtr obj, object::argsContainer& args)
{
    name::initialize(std::any_cast<name::initializationPack>(args[0]->getValue()));
    object::initialize(obj->READ(name("Root"), true));

    obj->READ(name("Root"), true)->addChild(makeObject(File, name("File"))
            ->addChild(makeObject(method<file, void (file::*)(std::string), &file::open, void, std::string>, name("open")))
            ->addChild(makeObject(method<file, void (file::*)(), &file::clear, void>, name("clear")))
            ->addChild(makeObject(method<file, std::string (file::*)(), &file::read, std::string>, name("read")))
            ->addChild(makeObject(method<file, std::string (file::*)(), &file::readAll, std::string>, name("readAll")))
            ->addChild(makeObject(FileWrite, name("write")))
        );
    return nullptr;
}
