#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <vector>

#include "user.hpp"

class ConfigReader{
public:
    ConfigReader(const std::string path);
    ConfigReader();
    std::vector<std::string> getFilesNames();
    std::vector<User> getUsers();
    void readConfigFile();
private:
    std::string path;
    std::vector<std::string> fileNames;
    std::vector<User> users;
};


#endif