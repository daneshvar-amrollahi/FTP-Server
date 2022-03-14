#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>
#include <string.h>
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
#include "CommandHandler.hpp"

const int MAX_THREADS = 1024;
const int COMMAND_PORT = 8080;
const int DATA_PORT = 8081;


class Server
{
public:
    Server(const std::string& config_path);
    void run();
    // void* handleConnection(void* arguments);

    ConfigReader configReader;
    std::vector<std::string> private_files;
    std::vector<User*> users;
};

#endif