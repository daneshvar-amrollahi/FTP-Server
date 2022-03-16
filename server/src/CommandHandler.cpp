#include "CommandHandler.hpp"

CommandHandler::CommandHandler(int data_fd, std::vector<User*> users) : data_fd(data_fd), users(users) {
    current_user = NULL;
    logged_in = false;
}

std::vector<std::string> CommandHandler::getSplitted(const std::string& s) {
    std::vector<std::string> res;
    std::string tmp = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            res.push_back(tmp);
            tmp = "";
        } else {
            tmp += s[i];
        }
    }
    res.push_back(tmp);
    return res;
}

std::string CommandHandler::runCommand(std::string input) {
    std::vector<std::string> splitted = getSplitted(input);
    std::string command = splitted[0];
    std::vector<std::string> args(splitted.begin() + 1, splitted.end());
    Response response;
    try
    {
        logger.writeMessage("Server Received COMMAND: " + command);
        if (command == "user"){
            return response.getMessage(handleUser(args[0]));
        } else
        if (command == "pass"){
            return response.getMessage(handlePass(args[0]));
        }
        else
        {
            throw SyntaxErrorInParamsOrArgs();
        }
    }
    catch(Exception& e) {
        return e.getError();
    }
}

int CommandHandler::handleUser(std::string username)
{
    if (logged_in)
        throw Exception();

    bool found = false;
    for (User* user: users) {
         if (user->username == username)
         {
            found = true;
            logging_in_user = user;
            logging_in = true;
         }
    }

    if (!found)
        throw InvalidUsernameOrPassword();
    return USERNAME_FOUND;
}

int CommandHandler::handlePass(std::string password) {
    if (!logging_in)
        throw BadSequenceOfCommands();
    
    if (logging_in_user->password == password)
    {
        logging_in = false;
        logged_in = true;
        current_user = logging_in_user;
        return USER_LOGGED_IN;
    }
    throw InvalidUsernameOrPassword();
}