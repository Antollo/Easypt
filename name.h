#ifndef NAME_H
#define NAME_H

#include <memory>
#include <map>
//TODO remove std::string and use something faster
class name
{
public:
    name(std::string textName);
    name(const char* textName);
    operator std::string() const
    {
        return (*codeToNameMap)[code];
    }
    operator int() const
    {
        return code;
    }
    bool operator ==(const name& x) const
    {
        return code == x;
    }
    //Why?
    //This class in dll will have own static members
    static void initialize();
    static void initialize(std::shared_ptr<std::map<int, std::string>>& newCodeToNameMap, std::shared_ptr<std::map<std::string, int>>& newNameToCodeMap);

private:
    int code;
    static std::shared_ptr<std::map<int, std::string>> codeToNameMap;
    static std::shared_ptr<std::map<std::string, int>> nameToCodeMap;
};

namespace std
{
template<>
struct hash<name>
{
    size_t operator()(const name & obj) const
    {
        return hash<int>()(obj);
    }
};
}

#endif // NAME_H
