#include "Server.hpp"
#include "CommandHandler.hpp"


Server::Server(const std::string& config_path) 
    : 
    configReader(ConfigReader(config_path)),
    private_files(configReader.getPrivateFiles()),
    users(configReader.getUsers()) {
    
}

void* handleConnection(void* command_fd, void* data_fd) {

    CommandHandler* commandHandler = new CommandHandler(*(int*) data_fd);

    while (true) {
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
}

