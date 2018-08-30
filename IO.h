#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>

namespace IO
{
    class _console
    {
    public:
        _console& operator<< (const std::string& text);
        _console& operator>> (std::string& text);
    };
    extern _console console;

    class _errorOut
    {
    public:
        _errorOut& operator<< (const std::string& text);
        _errorOut& operator<< (const int& number);
    };
    extern _errorOut errorOut;
};

#endif // IO_H
