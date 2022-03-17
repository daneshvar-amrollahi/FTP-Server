#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "Logger.hpp"
#include "User.hpp"
#include "Response.hpp"
#include "Exception.hpp"

class CommandHandler
{
public:
    CommandHandler(int data_fd, std::vector<User*> users);
    std::string runCommand(std::string input);
    int handleUser(std::string username);
    int handlePass(std::string password);
    std::string handlePwd(std::vector<std::string> args);
    std::string handleMkd(std::vector<std::string> args);
    std::string execShellCommand(const char *command, std::vector<std::string> args);


private:
    std::vector<std::string> getSplitted(const std::string& s);
    int data_fd;
    std::vector<User*> users; 
    Logger logger;
    User* current_user;
    bool logged_in;
    bool logging_in;
    User* logging_in_user;
    bool is_admin;
};

#endif