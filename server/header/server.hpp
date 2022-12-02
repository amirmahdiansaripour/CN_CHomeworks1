#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <vector>

#include "user.hpp"

class Server{
public:
    Server(const std::string configPath);
    void run();

private:
    // ConfigReader configReader;
    std::vector<std::string> fileNames;
    std::vector<User> users;
};

#endif