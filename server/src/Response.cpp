#include <Response.hpp>

#include <iostream>
#include <string>

std::string Response::getMessage(int code) {
    if (code == USERNAME_FOUND)
        return "331: User name okay, need password.";
    if (code == USER_LOGGED_IN)
        return "230: User logged in, proceed. Logged out if appropriate.";
    return "response";
}

std::string Response::getMessage(int code, std::string response) {
    if (code == PWD_OK)
        return "257: " + response;
    if (code == MKD_OK)
        return "257: " + response + " created.";
    return "response";
}

