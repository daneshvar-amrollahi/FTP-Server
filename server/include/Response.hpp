#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <string>

#define USERNAME_OK 331
//define other ones later

class Response
{
public:
    std::string getMessage(int num);
};

#endif