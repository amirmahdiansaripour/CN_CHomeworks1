#ifndef SERVER_H
#define SERVER_H

#include "user.hpp"
#include "configReader.hpp"

#include <string>
#include <vector>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>

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