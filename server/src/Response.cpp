#include <Response.hpp>

#include <iostream>
#include <string>

std::string Response::getMessage(int code) {
    if (code == USERNAME_FOUND)
        return "331: User name okay, need password.";
    if (code == USER_LOGGED_IN)
        return "230: User logged in, proceed. Logged out if appropriate.";
    if (code == LS_OK)
        return "226: List transfer done.";
    if (code == HELP_OK)
        return HELP_MESSAGE;
    if (code == RENAME_OK)
        return "250: Successful change";
    return "response";
}

std::string Response::getMessage(int code, std::string response) {
    if (code == PWD_OK)
        return "257: " + response;
    if (code == MKD_OK)
        return "257: " + response + " created.";
    if (code == DELE_OK)
        return "250: " + response + " deleted.";
    return "response";
}

