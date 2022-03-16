#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <string>

#define USERNAME_FOUND  331
#define USER_LOGGED_IN  230

class Response
{
public:
    std::string getMessage(int num);
};

#endif