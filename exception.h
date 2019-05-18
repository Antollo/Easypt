#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class exception : public std::exception
{
    public:
        template <class... Args>
        exception(std::string newSignature, std::string a1, std::string a2, Args... a3) : exception(newSignature, a1 + a2, a3...) {}
        exception(std::string newSignature, std::string newMessage) : signature(newSignature), message(newMessage) {}
        //exception(std::string newMessage) : message(newMessage) {}
        //exception(const char* newMessage) : message(newMessage) {}
        const char* what() const override { return message.c_str(); }
        const std::string& getSignature() const { return signature; };
        const std::string& getMessage() const { return message; };

    private:
        std::string message, signature;
};

#define WrongTypeOfArgument(...) exception("WrongTypeOfArgumentException", "WrongTypeOfArgumentException: ", __VA_ARGS__)
#define WrongNumberOfArguments(...) exception("WrongNumberOfArgumentsException", "WrongNumberOfArgumentsException: ", __VA_ARGS__)
#define FileNotFound(...) exception("FileNotFoundException", "FileNotFoundException: ", __VA_ARGS__)
#define OutOfRange(...) exception("OutOfRangeException", "OutOfRangeException: ", __VA_ARGS__)
#define NotSupportedOnThisOS(...) exception("NotSupportedOnThisOSException", "NotSupportedOnThisOSException: ", __VA_ARGS__)
#define InvalidValue(...) exception("InvalidValueException", "InvalidValueException: ", __VA_ARGS__)
#define Parser(...) exception("ParserException", "ParserException: ", __VA_ARGS__)
#define NotFound(...) exception("NotFoundException", "NotFoundException: ", __VA_ARGS__)
#define Arithmetic(...) exception("ArithmeticException", "ArithmeticException: ", __VA_ARGS__)
#define Unknown(...) exception("Exception", "Exception: ", __VA_ARGS__)
#define ExceptionAt(...) exception("ExceptionAt", "ExceptionAt: ", __VA_ARGS__)


#endif
