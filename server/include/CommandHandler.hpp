#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

#include <string>

class CommandHandler
{
public:
    CommandHandler(int data_fd);
    std::string runCommand(std::string input);

private:
    int data_fd;
};

#endif