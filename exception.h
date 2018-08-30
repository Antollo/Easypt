#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class exception : public std::exception
{
    public:
        template <class... Args>
        exception(std::string p1, std::string p2, Args... p3): exception(p1 + p2 ,p3...) {}
        exception(std::string newInfo) : info(newInfo) {}
        exception(const char* newInfo) : info(newInfo) {}
        const char* what() { return info.c_str(); }

    private:
        std::string info;
};

#endif // EASYPTEXCEPTION_H
