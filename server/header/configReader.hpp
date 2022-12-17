#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "user.hpp"
#include "Json.hpp"

using json = nlohmann::json;

class ConfigReader{
public:
    ConfigReader(const std::string path);
    ConfigReader();
    std::vector<std::string> getAdminFiles();
    std::vector<User*> getUsers();
    void readConfigFile();
    void printData();
    // void addUser(auto record);
private:
    std::string path;
    std::vector<std::string> adminFiles;
    std::vector<User*> users;
};


#endif