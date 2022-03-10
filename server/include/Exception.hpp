#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

class Exception
{
public:
    virtual void printError();
    int getNumber();

protected:
    std::string error = "";
    int number;
};

//introduce subclasses of exception for each error

#endif