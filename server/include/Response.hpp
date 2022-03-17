#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <string>

const int USERNAME_FOUND    =  331;
const int USER_LOGGED_IN    =  230;
const int PWD_OK            =  257;
const int MKD_OK            =  258;
const int DELE_OK           =  250;

class Response
{
public:
    std::string getMessage(int code);
    std::string getMessage(int code, std::string response);
};

#endif