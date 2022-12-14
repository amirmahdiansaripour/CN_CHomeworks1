#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <vector>

#include "user.hpp"
#include "configReader.hpp"

class Server{
public:
    Server(const std::string configPath);
    void run();
    void* handleConnection(void* command, void* command_id);

private:
    ConfigReader configReader;
    std::vector<std::string> fileNames;
    std::vector<User> users;
    int setupServer(int port);
    int acceptClient(int serverFd);
};

#endif