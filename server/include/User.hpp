#ifndef __USER_H__
#define __USER_H__

#include <string>

class User
{
public:
    User(
        const std::string& username = "NULL",
        const std::string& password = "NULL",
        const int& download_capacity = 0,
        const bool& admin = false
    );

    
    std::string username;
    std::string password;
    int download_capacity;
    bool admin;
};

#endif