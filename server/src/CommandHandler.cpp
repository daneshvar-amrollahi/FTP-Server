#include "CommandHandler.hpp"
#include "Response.hpp"

CommandHandler::CommandHandler(int data_fd) : data_fd(data_fd) {

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


    /*
    Response response;
    try
    {
        logger.writeMessage("Command " + command + " Requested.");
        if (command == "user")
            return response.getMessage(handleUser(...));

    }
    catch(...)
    */
   return "response"; //remove later
}

int CommandHandler::handleUser(std::string username)
{
    /*if not logged in
        throw exception
    
    ... (logic)

    */
    return USERNAME_OK;
}