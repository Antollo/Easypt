#include "name.h"

std::shared_ptr<std::map<int, std::string>> name::codeToNameMap;
std::shared_ptr<std::map<std::string, int>> name::nameToCodeMap;

name::name(std::string textName)
{
    //TODO exception
    if (textName.size() == 0) throw ("problem here");
    if (nameToCodeMap->count(textName) == 0)
    {
        code = nameToCodeMap->size();
        (*nameToCodeMap)[textName] = code;
        (*codeToNameMap)[code] = textName;
    }
    else
    {
        code = (*nameToCodeMap)[textName];
    }
}

name::name(const char* c_textName)
: name(std::string(c_textName)) {}

void name::initialize()
{
    codeToNameMap = std::make_shared<std::map<int, std::string>>();
    nameToCodeMap = std::make_shared<std::map<std::string, int>>();
}

void name::initialize(std::shared_ptr<std::map<int, std::string>>& newCodeToNameMap, std::shared_ptr<std::map<std::string, int>>& newNameToCodeMap)
{
    codeToNameMap = newCodeToNameMap;
    nameToCodeMap = newNameToCodeMap;
}
