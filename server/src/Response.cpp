#include <Response.hpp>

#include <iostream>
#include <string>

std::string Response::getMessage(int num) {
    if (num == USERNAME_FOUND)
        return "331: User name okay, need password.";
    if (num == USER_LOGGED_IN)
        return "230: User logged in, proceed. Logged out if appropriate.";
    return "response";
}

