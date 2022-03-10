#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

#include <string>

#include "Logger.hpp"

class CommandHandler
{
public:
    CommandHandler(int data_fd);
    std::string runCommand(std::string input);
    int handleUser(std::string username);
    //add similar methods for each command

private:
    int data_fd;
    static Logger logger;
};

#endif