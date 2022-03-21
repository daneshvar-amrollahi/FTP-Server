#include "Client.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <iostream>

Client::Client() {
    //I guess this will always be empty
}

int connectServer(int port)
{
    int fd;
    struct sockaddr_in server_address;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cout<<"Error in connecting to server\n";
        return -1;
    }
    return fd;
}

bool needsDataChannel(std::string command) //may need to be completed later
{
    return (command.substr(0, 2) == "ls") || (command.substr(0, 4) == "retr");
}

void Client::run() {
    std::string command;
    int command_fd,data_fd;
    command_fd = connectServer(8080);
    data_fd = connectServer(8081);
    // std::cout << "CLIENT connected: " << command_fd << " " << data_fd << std::endl;
    char read_buffer[1024];
    while(std::getline(std::cin, command)){
        send(command_fd, command.c_str(), command.size(), 0);

        recv(command_fd, read_buffer, sizeof(read_buffer), 0);
        std::cout << read_buffer << std::endl;

        if (needsDataChannel(command)) {
            recv(data_fd, read_buffer, sizeof(read_buffer), 0);
            std::cout << read_buffer << std::endl;
        }
    }
    
}