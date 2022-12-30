#include "../header/RequestHandler.hpp"
#include "../header/exception/Error404.hpp"

#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

const std::string HOME_FILE = "home.html";
const std::string HTML = "html";
const std::string GIF = "gif";
const std::string MP3 = "mp3";
const std::string JPEG = "jpeg";
const std::string JPG = "jpg";
const std::string PDF = "pdf";
const std::string CSS = "css";

const int BYTE_SIZE = 4;
typedef unsigned char imgByte;
const std::string FAVICON_REQ_NAME = "favicon.ico";
const std::string ERROR_404_FILE = "404.html";
const std::string CONTENT_DIRECTORY = "content/";
const std::string FAVICON_FILE_NAME = CONTENT_DIRECTORY + "favicon.png";

RequestHandler::RequestHandler() {}

std::string RequestHandler::handleGetRequest(std::string request)
{
    std::string fileName = getFileName(request);
    std::string fileNameForRead = CONTENT_DIRECTORY + fileName;
    std::string fileType = getFileType(fileName);
    std::string fileContent;
    try{
        if(fileName == FAVICON_REQ_NAME)
        {
            fileContent = getBinaryFileContent(FAVICON_FILE_NAME);
            return fileResponse(fileContent, getContentType(JPG));
        }
        else if(fileType == HTML || fileType == CSS)
        {
            fileContent = getTextFileContent(fileNameForRead);
            return fileResponse(fileContent, getContentType(fileType));
        }
        else if(fileType == JPEG || fileType == JPG || fileType == GIF || fileType == MP3 || fileType == PDF)
        {
            fileContent = getBinaryFileContent(fileNameForRead);
            return fileResponse(fileContent, getContentType(fileType));
        }
        else
        {
            std::exception* ex = new Error404();
            throw ex;
        }
    } catch(std::exception* ex)
    {
        std::cout << ex->what() << "\n";

        fileContent = getTextFileContent(CONTENT_DIRECTORY + ERROR_404_FILE);
        delete ex;
        return fileResponse(fileContent, HTML);
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
    
    std::string fileName;
    ss >> fileName;
    
    fileName.erase(0,1);
    
    if(fileName == "")
    {
        fileName = HOME_FILE;
    }
    return fileName;
}

std::string RequestHandler::getTextFileContent(std::string address)
{
    std::ifstream fileReader(address);
    std::string content;
    if(!fileReader.is_open())
    {
        std::exception* ex = new Error404();
        throw ex;
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

std::string RequestHandler::fileResponse(std::string content, std::string contentType)
{
    std::ostringstream ss;
        ss << "HTTP/1.1 200 OK\nContent-Type: " << contentType << "\nContent-Length: " << content.size() << "\n\n"
           << content;
    return ss.str();
}

std::string RequestHandler::getContentType(std::string fileType)
{
    if(fileType == HTML)
        return "text/html";
    else if(fileType == JPEG || fileType == JPG)
        return  "image/jpeg";  
    else if(fileType == PDF)
        return "application/pdf";
    else if(fileType == MP3)
        return "audio/mpeg";
    else if(fileType == GIF)
        return "image/gif";
    else if(fileType == CSS)
        return "text/css";
    else
    {
        std::exception* ex = new Error404();
        throw ex;
    }
}

std::string RequestHandler::getBinaryFileContent(std::string address)
{
    std::ifstream binaryReader(address, std::ios::in | std::ios::binary);
    std::filebuf* pbuf = binaryReader.rdbuf();

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(binaryReader), {});

    if(!binaryReader.is_open())
    {
        std::exception* ex = new Error404();
        throw ex;
    }

    std::string content{buffer.begin(), buffer.end()};
    binaryReader.close();

    return content;
}


