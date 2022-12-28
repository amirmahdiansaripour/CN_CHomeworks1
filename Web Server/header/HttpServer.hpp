#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>

const std::string HOME_FILE = "home.html";
class HttpServer {
    public:
        HttpServer(std::string ipAddress_, int port_);
        ~HttpServer();
        void run();
    private:
        int serverFd;
        int port;
        int newSocket;
        std::string ipAddress;
        struct sockaddr_in socketAddress;
        socklen_t socketAddressSize;
        void startServer();
        int acceptConnection();
        void sendResponse(std::string response);
        std::string getFileName(std::string response);
        std::string createResponse(std::string fileName);
        std::string getFileContent(std::string address);
};



#endif
