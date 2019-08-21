#include "name.h"

std::map<int, std::string> name::codeToNameMap;
std::map<std::string, int> name::nameToCodeMap;

name::name(std::string textName)
{

    if (textName.size() == 0) throw(Parser("Terrible parser error"));
    if (nameToCodeMap.count(textName) == 0)
    {
        code = nameToCodeMap.size();
        nameToCodeMap[textName] = code;
        codeToNameMap[code] = textName;
    }
    else
    {
        code = nameToCodeMap[textName];
    }
}

name::name(const char* c_textName)
: name(std::string(c_textName)) {}
