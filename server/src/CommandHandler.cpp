#include "CommandHandler.hpp"

CommandHandler::CommandHandler(int data_fd) : data_fd(data_fd) {

}

std::string runCommand(std::string input) {
    //extract command and arguments from input using CommandParser

    //swith case on command and call appropriate method

    //write message using logger

    return "response"; //fix later
}