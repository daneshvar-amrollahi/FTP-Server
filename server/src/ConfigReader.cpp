#include "ConfigReader.hpp"

ConfigReader::ConfigReader(const std::string& file_path) : file_path(file_path) {
    readConfig();
}

void ConfigReader::readConfig() {
    //parse json file and fill the vectors: users + private_files
}

std::vector<User> ConfigReader::getUsers()
{
    return users;
}

std::vector<std::string> ConfigReader::getPrivateFiles()
{
    return private_files;
}

