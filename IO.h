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

    class _log
    {
    public:
        _log& operator<< (const std::string& text);
        _log& operator<< (const int& number);
        _log& operator<< (const double& number);
        _log& operator<< (const bool& boolean);
        _log& operator<< (const char* text);
    };
    extern _log log;
};

#endif // IO_H
