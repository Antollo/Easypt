#include <fstream>
#include <memory>
#include "nobject.h"
#include "Common.h"
#include "Core.h"

class file
{
public:
    file() : f(std::make_shared<std::fstream>()) {}
    file(const file& anotherFile) : f(anotherFile.f), fileName(anotherFile.fileName) {}
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

object::objectPtr File (object::objectPtr obj, object::arrayType& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addPrototypeChild(child.second);
    ret->getValue() = file();
    return ret;
};

object::objectPtr FileWrite (object::objectPtr obj, object::arrayType& args)
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

object::objectPtr initFile (object::objectPtr obj, object::arrayType& args)
{
    obj->READ(name("Root"), true)->addChild(makeClass({
        obj->READ("Object", true),
        makeObject((object::nativeFunctionType)[](object::objectPtr obj, object::arrayType& args) -> object::objectPtr {
            obj->getParent()->getValue() = file();
            return obj->getParent();
        }, name("File")),
        makeObject(method<file, void (file::*)(std::string), &file::open, void, std::string>, name("open")),
        makeObject(method<file, void (file::*)(), &file::clear, void>, name("clear")),
        makeObject(method<file, std::string (file::*)(), &file::read, std::string>, name("read")),
        makeObject(method<file, std::string (file::*)(), &file::readAll, std::string>, name("readAll")),
        makeObject(FileWrite, name("write")),
    })->setName("File"));
    //object::release();
    return nullptr;
}
