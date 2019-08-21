#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include "nobject.h"

std::map<object::nativeFunctionType, std::string> locationToFilename;
inline size_t findNth(const std::string& str, const std::string& what, size_t n, size_t pos = 0)
{
	if (pos == std::string::npos) return pos;
	if (n == 1) return str.find(what, pos);
	return findNth(str, what, n-1, str.find(what, pos) + 1);
}
inline std::string goodName(const std::string& oldName)
{
	std::size_t pos;
	std::string temp="less", name = oldName;
	while ((pos = name.find('<')) != std::string::npos)
		name.replace(name.begin()+pos, name.begin()+pos+1, temp.begin(), temp.end());
	temp="greater";
	while ((pos = name.find('>')) != std::string::npos)
		name.replace(name.begin()+pos, name.begin()+pos+1, temp.begin(), temp.end());
	temp="star";
	while ((pos = name.find('*')) != std::string::npos)
		name.replace(name.begin()+pos, name.begin()+pos+1, temp.begin(), temp.end());
	temp="tilde";
	while ((pos = name.find('~')) != std::string::npos)
		name.replace(name.begin()+pos, name.begin()+pos+1, temp.begin(), temp.end());
	temp="div";
	while ((pos = name.find('/')) != std::string::npos)
		name.replace(name.begin()+pos, name.begin()+pos+1, temp.begin(), temp.end());
    return name;
}
object::objectPtr generateDocs (object::objectPtr obj, object::arrayType& args)
{
    if (args.size() == 1)
    {
        std::string temp, fileContent, description = "\n\n", example = "\n\n";
        IO::console << "Processing: " << args[0]->getFullNameString() << "\n";
        if (args[0]->hasSignature("NativeCallable"))
        {
            object::nativeFunctionType f = std::any_cast<object::nativeFunctionType>(args[0]->getValue());
            if (locationToFilename.count(f)) IO::console << "Probably duplicate\n";
        }

        if (std::ifstream(("docs/docs" + goodName(args[0]->getFullNameString()) + ".md").c_str()).good())
        {
            IO::console << "Update file? (y/n) ";
            do {
                IO::console >> temp;
            } while (temp != "y" && temp != "n");
            if (temp == "n") return args[0];
        }
        else
        {
            IO::console << "Create file? (y/n) ";
            do {
                IO::console >> temp;
            } while (temp != "y" && temp != "n");
            if (temp == "n") return args[0];
            std::ofstream("docs/docs" + goodName(args[0]->getFullNameString()) + ".md");
            if (args[0]->hasSignature("Callable")) description = "\n\n* **Parameters:**\n\n* **Return value:**\n\n";
        }

        object::arrayType container;
        for (auto& child : args[0]->getChildren())
        {
            container = object::arrayType(1, child.second);
            generateDocs(obj, container);
        }

        if (args[0]->hasSignature("NativeCallable") && std::isupper(((std::string)args[0]->getName())[0]) )
        {
            object::nativeFunctionType f = std::any_cast<object::nativeFunctionType>(args[0]->getValue());
            if (locationToFilename.count(f) == 0) locationToFilename[f] = "docs/docs" + goodName(args[0]->getFullNameString()) + ".md";
        }

        std::ifstream fileInput("docs/docs" + goodName(args[0]->getFullNameString()) + ".md");
	    std::getline(fileInput, fileContent, '\0');
        fileInput.close();
        if (findNth(fileContent, "`", 4) != std::string::npos) description = fileContent.substr(findNth(fileContent, "`", 4) + 1, fileContent.find("## Child of:") - findNth(fileContent, "`", 4) - 1);
	    if (fileContent.find("## Example:") != std::string::npos) example = fileContent.substr(fileContent.find("## Example:") + std::string("## Example:").size());
        
        std::ofstream fileOutput("docs/docs" + goodName(args[0]->getFullNameString()) + ".md", std::ofstream::trunc);
        fileOutput << "# `" << (std::string)args[0]->getName() << "`\n\n";
        
        fileOutput << "#### `" << args[0]->getFullNameString() << "`";
        fileOutput << description;
        
        fileOutput << "## Child of:\n\n[`" << (std::string)args[0]->getParent()->getName() << "`](" << "docs" + args[0]->getParent()->getFullNameString() + ".md" << ")\n\n";
        
        fileOutput << "## Signatures:\n\n";
        for (auto& signature : args[0]->getSignatures())
            fileOutput << "`" << (std::string)signature << "`, ";
        if (args[0]->getSignatures().size())
            fileOutput.seekp((int)fileOutput.tellp() - 2);
        
        if (args[0]->getChildren().size()) fileOutput << "\n\n## Members:\n";
        fileOutput << "\n";
        for (auto& child : args[0]->getChildren())
        {
            fileOutput << "- [`" << (std::string)child.second->getName() << "`]";
            if (child.second->hasSignature("NativeCallable"))
            {
                object::nativeFunctionType f = std::any_cast<object::nativeFunctionType>(child.second->getValue());
                if (locationToFilename.count(f)) fileOutput << "(" << locationToFilename[f] << ")\n";
                else fileOutput << "(" << "docs" + child.second->getFullNameString() + ".md" << ")\n";
            }
            else fileOutput << "(" << "docs" + child.second->getFullNameString() + ".md" << ")\n";
        }
        fileOutput << "\n\n## Example:\n\n" << example;
        fileOutput.close();
        return args[0];
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}

void _generateDocsImpl (object::objectPtr arg)
{
    if (arg->getValue().type().hash_code() == typeid(std::string).hash_code())
        std::cerr << "\033[91m\033[1m" << *std::any_cast<std::string>(&arg->getValue()) << "\033[0m" << std::endl;
    else if (arg->getValue().type().hash_code() == typeid(int).hash_code())
        std::cerr << "\033[91m\033[1m" << *std::any_cast<int>(&arg->getValue()) << "\033[0m" << std::endl;
    else if (arg->getValue().type().hash_code() == typeid(bool).hash_code())
        std::cerr << "\033[91m\033[1m" << *std::any_cast<bool>(&arg->getValue()) << "\033[0m" << std::endl;
    else if (arg->getValue().type().hash_code() == typeid(double).hash_code())
        std::cerr << "\033[91m\033[1m" << *std::any_cast<double>(&arg->getValue()) << "\033[0m" << std::endl;
    else if (arg->getValue().type().hash_code() == typeid(object::arrayType).hash_code())
    {
        for(auto& el : *std::any_cast<object::arrayType>(&arg->getValue()))
        {
            _generateDocsImpl(el);
        }
    }
}

object::objectPtr _generateDocs (object::objectPtr obj, object::arrayType& args)
{
    for(auto& arg : args)
        _generateDocsImpl(arg);
    return obj;
}

object::objectPtr initDocs (object::objectPtr obj, object::arrayType& args)
{
    obj->addChild(makeObject(_generateDocs, name("callOperator")));
    return nullptr;
}

