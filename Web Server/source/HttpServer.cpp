#include "../header/HttpServer.hpp"
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

        //std::cout <<  "Client Request: " << std::string(buffer) << "\n";
        std::string fileName = getFileName(std::string(buffer));
        std::cout << "Received request from client\n";
        std::string fileContent = getFileContent(fileName);
        sendResponse(createResponse(fileName));

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

std::string HttpServer::createResponse(std::string fileName)
{
    if(fileName == "")
    {
        fileName = HOME_FILE;   
    }
    std::string fileContent = getFileContent(fileName);
    
    std::ostringstream ss;
        ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << fileContent.size() << "\n\n"
           << fileContent;
    return ss.str();
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

std::string HttpServer::getFileName(std::string response)
{
    std::stringstream ss;
    ss << response;

    std::string item, res;
    res = "";
    while(true)
    {
        ss >> item;
        res += item;
        if(item == "GET")
            break;
    }
    
    std::cout << "Pre Get Content: " << res << "\n";
    std::string fileName;
    ss >> fileName;
    fileName.erase(0,1);

    std::cout << "Filename " << fileName << "\n";
    return fileName;
}

std::string HttpServer::getFileContent(std::string address)
{
    std::ifstream fileReader(address);
    std::string content;

    if(!fileReader.is_open())
    {
        content = "<!DOCTYPE html> <html lang=\"en\"> <body> <h1> HOME </h1> <p> 404 Error </p> </body> </html>";
        return content;
    }

    while(!fileReader.eof())
    {
        content += fileReader.get();
    }
    fileReader.get();

    return content;

}