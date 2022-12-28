#include "../header/RequestHandler.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

RequestHandler::RequestHandler() {}

std::string RequestHandler::handleGetRequest(std::string request)
{
    std::string fileName = getFileName(request);
    std::string fileType = getFileType(fileName);
    std::string fileContent = getFileContent(fileName);

    if(fileType == HTML)
    {
        return htmlFileResponse(fileContent);
    }
}

std::string RequestHandler::getFileName(std::string response)
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
    
    if(fileName == "")
    {
        fileName = HOME_FILE;
    }
    std::cout << "Filename " << fileName << "\n";
    return fileName;
}

std::string RequestHandler::getFileContent(std::string address)
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
    fileReader.close();


    return content;

}

std::string RequestHandler::getFileType(std::string fileName)
{
    std::stringstream ss;
    ss << fileName;

    std::string fileType;
    while(std::getline(ss, fileType, '.')){}
    return fileType;

}

std::string RequestHandler::htmlFileResponse(std::string content)
{
    std::ostringstream ss;
        ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << content.size() << "\n\n"
           << content;
    return ss.str();
}