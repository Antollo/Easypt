#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class exception : public std::exception
{
    public:
        template <class... Args>
        exception(std::string signature, std::string a1, std::string a2, Args... a3): exception(signature, a1 + a2, a3...) {}
        exception(std::string newSignature, std::string newMessage) : signature(newSignature), message(newMessage) {}
        exception(std::string newMessage) : message(newMessage) {}
        exception(const char* newMessage) : message(newMessage) {}
        const char* what() { return message.c_str(); }
        std::string& getSignature() { return signature; };
        std::string& getMessage() { return message; };

    private:
        std::string signature, message;
};

#define WrongTypeOfArgument(...) exception("WrongTypeOfArgumentException", "WrongTypeOfArgumentException: ", __VA_ARGS__)
#define WrongNumberOfArguments(...) exception("WrongTypeOfArgumentsException", "WrongTypeOfArgumentsException: ", __VA_ARGS__)
#define FileNotFound(...) exception("FileNotFoundException", "FileNotFoundException: ", __VA_ARGS__)
#define OutOfRange(...) exception("OutOfRangeException", "OutOfRangeException: ", __VA_ARGS__)
#define NotSupportedOnThisOS(...) exception("NotSupportedOnThisOSException", "NotSupportedOnThisOSException: ", __VA_ARGS__)
#define InvalidValue(...) exception("InvalidValueException", "InvalidValueException: ", __VA_ARGS__)
#define Parser(...) exception("ParserException", "ParserException: ", __VA_ARGS__)
#define NotFound(...) exception("NotFoundException", "NotFoundException: ", __VA_ARGS__)
#define Arithmetic(...) exception("ArithmeticException", "ArithmeticException: ", __VA_ARGS__)


#endif
