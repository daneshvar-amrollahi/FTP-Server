#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>
#include <string>
#include <thread>
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <iostream>

#include "User.hpp"
#include "ConfigReader.hpp"

const int MAX_THREADS = 1024;
const int COMMAND_PORT = 8080;
const int DATA_PORT = 8081;


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