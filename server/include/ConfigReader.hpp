#ifndef __CONFIG_READER_H__
#define __CONFIG_READER_H__

#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include <iostream>

#include "User.hpp"
#include "Json.hpp"
using json = nlohmann::json;


class ConfigReader
{
public:
    ConfigReader(const std::string& file_path);
    std::vector<std::string> getPrivateFiles();
    std::vector<User*> getUsers();
    int getCommandChannelPort();
    int getDataChannelPort();
    
private:
    std::string file_path;
    std::vector<std::string> private_files;
    std::vector<User*> users;
    int commandChannelPort;
    int dataChannelPort;
    void readConfig();
};

#endif
