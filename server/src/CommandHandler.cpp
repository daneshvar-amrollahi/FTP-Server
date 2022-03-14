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
        }
    }
    catch(Exception& e) {
        return response.getMessage(e.getNumber());
    }
    
   return "response"; //remove later
}

int CommandHandler::handleUser(std::string username)
{
    if (logged_in)
        throw Exception();

    std::string logging_in_username;
    for (User* user: users) {
         if (user->username == username)
         {
             logging_in_username = user->username;
             logging_in = true;
         }
    }
    return USERNAME_FOUND;
}