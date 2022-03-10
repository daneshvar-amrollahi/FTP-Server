#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>
#include <string>

#include "User.hpp"
#include "ConfigReader.hpp"

class Server
{
public:
    Server(const std::string& config_path);
    void run();
    void* handle_connection(void* command_fd, void* data_fd);

private:
    ConfigReader configReader;
    std::vector<std::string> private_files;
    std::vector<User> users;
};

#endif