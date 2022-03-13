#include "Server.hpp"
#include "CommandHandler.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <iostream>


Server::Server(const std::string& config_path) 
    : 
    configReader(ConfigReader(config_path)),
    private_files(configReader.getPrivateFiles()),
    users(configReader.getUsers()) {
}

int setupServer(int port) {
    struct sockaddr_in address;
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    
    listen(server_fd, 4);

    return server_fd;
}

int acceptClient(int server_fd) {
    int client_fd;
    struct sockaddr_in client_address;
    int address_len = sizeof(client_address);
    
    client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t*) &address_len);

    return client_fd;
}

void handleConnection(int command_fd, int data_fd) {

    int bytes_received;
    char buffer[1024];
    std::string message;
    CommandHandler* commandHandler = new CommandHandler(data_fd);
    while (true) {
        memset(buffer, 0, 1024);
        bytes_received = recv(command_fd , buffer, 1024, 0);
        if (bytes_received == 0) { // EOF
            std::cout<<"Client "<< command_fd<< "Closed Connection\n";
            close(command_fd);
            close( data_fd);
        }else{
            message=std::string(buffer);
            //Call command handler here
            std::cout<<"User "<<command_fd<<" Said:"<<message<<std::endl;
        }
        //recv commands from channels and call commandHandler->runCommand()
    }
}

void Server::run() {
    /*socket mocket stuff!
    
    while (true) {
        accept connections from both channels (data and command)..

        create new thread and handle connection..
    }

    join threads*/
    int data_fd,command_fd,max_fd,new_client_fd, data_port=8080,command_port=8081,data_socket,command_socket;
    fd_set master_set, working_set;
    int bytes_received;
    char buffer[1024];
    std::string message;

    data_fd=setupServer(data_port);
    command_fd=setupServer(command_port);
    max_fd=std::max(command_fd,data_fd);
    std::cout<<"server is ready"<<std::endl;

    FD_SET(data_fd, &master_set);
    FD_SET(command_fd, &master_set);

    while (true)
    {
        working_set = master_set;
        select(max_fd + 1, &working_set, NULL, NULL, NULL);
        for (int i = 0; i <= max_fd; i++) {
            if(!FD_ISSET(i, &working_set))
                continue;
            if (i==data_fd) {    
                data_socket = acceptClient(data_fd);
                FD_SET(data_socket, &master_set);
                std::cout<<"Client Connected to Data Port"<<std::endl;
                if(data_socket>max_fd){
                    max_fd=data_socket;
                }
            }
            else if(i==command_fd){
                command_socket = acceptClient(command_fd);
                FD_SET(command_socket, &master_set);
                std::cout<<"Client Connected to Command Port"<<std::endl;
                if(command_socket>max_fd){
                    max_fd=command_socket;
                }
                handleConnection(command_socket,data_socket);
            }
            else{
                memset(buffer, 0, 1024);
                bytes_received = recv(i , buffer, 1024, 0);
                if (bytes_received == 0) { // EOF
                    std::cout<<"Client "<< i<< "Closed Connection\n";
                    close(i);
                }else{
                    message=std::string(buffer);
                    //Call command handler here
                    std::cout<<"User "<<i<<" Said:"<<message<<std::endl;
                }
            }
        }
    }
}

