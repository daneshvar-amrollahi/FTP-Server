#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

class Exception
{
public:
    int getNumber();

protected:
    std::string error = "";
    int number = 500;
};

//introduce subclasses of exception for each error

#endif