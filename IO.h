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

    class _basicOut
    {
    public:
        _basicOut& operator<< (const std::string& text);
        _basicOut& operator<< (const int& number);
        _basicOut& operator<< (const double& number);
    };
    extern _basicOut basicOut;
};

#endif // IO_H
