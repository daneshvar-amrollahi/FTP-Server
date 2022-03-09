#include "Server.hpp"


Server::Server(const std::string& config_path) 
    : 
    configReader(ConfigReader(config_path)),
    private_files(configReader.getPrivateFiles()),
    users(configReader.getUsers()) {
    
}

void Server::run() {
    
}

