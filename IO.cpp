#include "IO.h"

IO::_console& IO::_console::operator<< (const std::string& text)
{
    std::cout<<text;
    return *this;
};

IO::_console& IO::_console::operator>> (std::string& text)
{
    std::cin>>text;
    return *this;
};

IO::_log& IO::_log::operator<< (const std::string& text)
{
    std::cout<<text<<std::endl;
    return *this;
};

IO::_log& IO::_log::operator<< (const int& number)
{
    std::cout<<number<<std::endl;
    return *this;
};

IO::_log& IO::_log::operator<< (const double& number)
{
    std::cout<<number<<std::endl;
    return *this;
};

IO::_log& IO::_log::operator<< (const bool& boolean)
{
    std::cout<<boolean<<std::endl;
    return *this;
};

IO::_log& IO::_log::operator<< (const char* text)
{
    std::cout<<text<<std::endl;
    return *this;
};

IO::_console IO::console;
IO::_log IO::log;
