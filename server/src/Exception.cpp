#include "Exception.hpp"

std::string Exception::getError()
{
    return message;
}

int Exception::getCode()
{
    return number;
}


int InvalidUsernameOrPassword::getCode()
{
    return code;
}

std::string InvalidUsernameOrPassword::getError()
{
    return error;
}

int SyntaxErrorInParamsOrArgs::getCode()
{
    return code;
}

std::string SyntaxErrorInParamsOrArgs::getError()
{
    return error;
}
