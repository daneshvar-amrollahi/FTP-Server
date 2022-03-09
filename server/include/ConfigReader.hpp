#ifndef __CONFIG_READER_H__
#define __CONFIG_READER_H__

#include <string>
#include <vector>

#include "User.hpp"

class ConfigReader
{
public:
    ConfigReader(const std::string& config_file_path);
    std::vector<std::string> getPrivateFiles();
    std::vector<User> getUsers();
    
private:
    std::string file_path;
    std::vector<std::string> private_files;
    std::vector<User> users;
    void readConfig();
};

#endif
