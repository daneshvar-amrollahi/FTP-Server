#include <Response.hpp>

#include <iostream>
#include <string>

std::string Response::getMessage(int num) {
    if (num == USERNAME_FOUND)
        return "331: User name okay, need password.";
    //add other ones later       
    return "response";
}

