#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

class Exception
{
public:
    int getNumber();
    std::string getError();
protected:
    std::string error = "500: Error";
    int number = 500;
};

class InvalidUsernameOrPassword : public Exception
{
private:
    std::string error = "430: Invalid username or password";
    int number = 430;
};

#endif