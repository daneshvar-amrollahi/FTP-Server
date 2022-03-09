#ifndef __USER_H__
#define __USER_H__

#include <string>

class User
{
public:
    User(
        const std::string& username,
        const std::string& password,
        const int& download_capacity,
        const bool& admin
    );
private:
    std::string username;
    std::string password;
    int download_capacity;
    bool admin;
};

#endif