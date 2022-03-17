#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

class Exception
{
    public:
        virtual std::string getError();

    private:
        const std::string message = "500: Error";
};

class InvalidUsernameOrPassword : public Exception
{
    public:
        virtual std::string getError();

    private:
        const std::string error = "430: Invalid username or password";
};

class SyntaxErrorInParamsOrArgs : public Exception
{
    public:
        virtual std::string getError();

    private:
        const std::string error = "501: Syntax error in parameters or arguments";
};

class BadSequenceOfCommands : public Exception
{
    public:
        virtual std::string getError();

    private:
        const std::string error = "503: Bad sequence of commands.";
};

class NotLoggedIn : public Exception
{
    public:
        virtual std::string getError();

    private:
        const std::string error = "332: Need account for login.";
};


#endif