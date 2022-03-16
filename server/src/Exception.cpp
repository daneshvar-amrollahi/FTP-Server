#include "Exception.hpp"

std::string Exception::getError()
{
    return message;
}

std::string InvalidUsernameOrPassword::getError()
{
    return error;
}

std::string SyntaxErrorInParamsOrArgs::getError()
{
    return error;
}

std::string BadSequenceOfCommands::getError()
{
    return error;
}
