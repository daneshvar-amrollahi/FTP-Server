#include "ConfigReader.hpp"

ConfigReader::ConfigReader(const std::string& file_path) : file_path(file_path) {
    readConfig();
}

void ConfigReader::readConfig() {
    std::ifstream fin(file_path);
    json j;
    fin >> j;
    for (auto& user: j["users"])
    {
        std::string username = user["user"].get<std::string>();
        std::string password = user["password"].get<std::string>();
        int download_capacity = stoi(user["size"].get<std::string>());
        bool admin = user["admin"].get<std::string>() == "true";
        User curUser = User(username, password, download_capacity, admin);
        users.push_back(curUser);
    }
    for (auto& file: j["files"])
        private_files.push_back(file.get<std::string>());
}

std::vector<User> ConfigReader::getUsers()
{
    return users;
}

std::vector<std::string> ConfigReader::getPrivateFiles()
{
    return private_files;
}

