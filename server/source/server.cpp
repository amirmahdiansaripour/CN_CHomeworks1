#include "../header/server.hpp"
#include "../header/messageHandler.hpp"

using namespace std;

#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(const string path){

    configReader = ConfigReader(path);
    fileNames = configReader.getFilesNames();
    users = configReader.getUsers();

}

void Server::run(){

}

void* Server::handleConnection(void* command, void* command_id){
    MessageHandler* messageHandler = new MessageHandler(*(int* ) command_id, users);
    // connections and reqs from clients are handled here.
}

int Server::setupServer(int port) 
{
    struct sockaddr_in address;
    int serverFd;

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    
    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(serverFd, (struct sockaddr*)& address, sizeof(address));

    listen(serverFd, 4);

    return serverFd;
}

int Server::acceptClient(int serverFd) 
{
    struct sockaddr_in clientAddress;
    int addressLen = sizeof(clientAddress);

    int clientFd = accept(serverFd, (struct sockaddr *)& clientAddress, (socklen_t*) &addressLen);

    return clientFd;
}