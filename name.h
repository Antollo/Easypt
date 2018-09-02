#ifndef NAME_H
#define NAME_H

#include <memory>
#include <map>
#include <cstring>
/*class fastString
{
public:
    fastString()
    : value(nullptr) {};
    fastString(const char* newValue)
    : fastString(newValue, std::strlen(newValue)) {};
    fastString(const char* newValue, size_t size)
    {
        if (size == 0) throw ("problem here");
        value = new char [size];
        std::strncpy(value, newValue, size);
    }
    ~fastString()
    {
    	delete [] value;
    }
    bool operator == (const fastString& another) const
    {
    	return  std::strcmp(value, another.value) == 0;
    }
    bool operator < (const fastString& another) const
    {
    	return  std::strcmp(value, another.value) < 0;
    }
    operator std::string() const
    {
        return std::string(value);
    }
private:
    char* value;
};*/

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
