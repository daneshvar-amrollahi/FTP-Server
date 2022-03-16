#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

class Exception
{
public:
    virtual std::string getError();
    virtual int getCode();

private:
    const std::string message = "500: Error";
    const int number = 500;
};

class InvalidUsernameOrPassword : public Exception
{
public:
    virtual std::string getError();
    virtual int getCode();

private:
    const std::string error = "430: Invalid username or password";
    const int code = 430;
};

class SyntaxErrorInParamsOrArgs : public Exception
{
public:
    virtual std::string getError();
    virtual int getCode();

private:
    const std::string error = "501: Syntax error in parameters or arguments";
    const int code = 430;
};



#endif