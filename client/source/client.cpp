#include "../header/client.hpp"

using namespace std;

#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>

Client::Client(){

}

void Client::run()
{
    string command;    
    
    int dataFd = connectServer(8080);
    int commandFd = connectServer(8081);

    while(true) 
    {
        getline(cin, command);
        send(commandFd, command.c_str(), command.size(), 0);
    }

}

int Client::connectServer(int port) 
{
    int fd;
    struct sockaddr_in serverAddress;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(fd, (struct sockaddr *)& serverAddress, sizeof(serverAddress)) < 0)
    {
        cout << "Error in connecting to server\n";
        return -1;
    }
    
    cout << "Connected to server at port " << port << "\n";
    return fd;

}