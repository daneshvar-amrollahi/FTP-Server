#include "CommandHandler.hpp"
#include "Response.hpp"

CommandHandler::CommandHandler(int data_fd) : data_fd(data_fd) {

}

std::string runCommand(std::string input) {

    //extract command and arguments from input using CommandParser

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