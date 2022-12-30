#include "../header/HttpServer.hpp"
#include "../header/RequestHandler.hpp"
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <iostream>

const int BUFFER_SIZE = 30720;

void error(std::string message)
{
    std::cout << "ERROR " << message << "\n";
    exit(1);
}

HttpServer::HttpServer(std::string ipAddress_, int port_)
{
    port = port_;
    ipAddress = ipAddress_;
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(port);
    socketAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    socketAddressSize = sizeof(socketAddress);
    startServer();

}

void HttpServer::startServer()
{
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverFd < 0)
    {
        error("Cannot create socket\n");
    }
    if( bind(serverFd, (sockaddr *) &socketAddress, socketAddressSize) < 0)
    {
        error("Cannot connect socket to address");
    }
}

HttpServer::~HttpServer()
{
    close(serverFd);
    exit(0);
}

void HttpServer::run()
{
    if(listen(serverFd, 10) < 0)
    {
        error("Listen failure\n");
    }
    
    std::cout << "Listening on address : " << inet_ntoa(socketAddress.sin_addr) << " port: " << ntohs(socketAddress.sin_port) << "\n";

    int bytesReceived;
    RequestHandler requestHandler;
    while (true) 
    {
        std::cout << "Waiting for a new connection\n";
        newSocket = acceptConnection();

        char buffer[BUFFER_SIZE] = {0};
        bytesReceived = read(newSocket, buffer, BUFFER_SIZE);
        if(bytesReceived < 0)
        {
            error("Failed to read bytes from client\n");
        }

        std::cout <<  "Client Request: " << std::string(buffer) << "\n";
        std::cout << "Received request from client\n";
        sendResponse(requestHandler.handleGetRequest(std::string(buffer)));

        close(newSocket);

    }

}

int HttpServer::acceptConnection()
{
    int newSocket = accept(serverFd, (sockaddr*) &socketAddress, &socketAddressSize);
    
    if(newSocket < 0)
    {
        error("Server failed to accept connection");
    }

    return newSocket;
}


void HttpServer::sendResponse(std::string response)
{
    long bytesSent;

    bytesSent = write(newSocket, response.c_str(), response.size());

    if(bytesSent == response.size())
    {
        std::cout << "Server response sent to client\n";
    }
    else
    {
        std::cout << "Error responding to client\n";
    }
}

