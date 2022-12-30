#include "../header/RequestHandler.hpp"

#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

const int BYTE_SIZE = 4;
typedef unsigned char imgByte;
const std::string FAVICON_REQ_NAME = "favicon.ico";
const std::string FAVICON_FILE_NAME = "favicon.png";
RequestHandler::RequestHandler() {}

std::string RequestHandler::handleGetRequest(std::string request)
{
    std::string fileName = getFileName(request);
    std::string fileType = getFileType(fileName);
    std::cerr << "fileType " << fileType << " || " << fileName << "\n";
    std::string fileContent;
    if(fileName == FAVICON_REQ_NAME)
    {
        std::cerr << "---------------HELLO---------\n\n\n\n\"";
        fileContent = getImageFileContent(FAVICON_FILE_NAME);
        return fileResponse(fileContent, getContentType(JPG));
    }
    else if(fileType == HTML)
    {
        fileContent = getTextFileContent(fileName);
        return fileResponse(fileContent, getContentType(fileType));
    }
    else if(fileType == JPEG || fileType == JPG)
    {
        fileContent = getImageFileContent(fileName);
        return fileResponse(fileContent, getContentType(fileType));
    }
}

std::string RequestHandler::getFileName(std::string response)
{
    std::stringstream ss;
    ss << response;

    std::cerr << "GETFILENAME " << response <<"\n";
    std::string item, res;
    res = "";
    while(true)
    {
        ss >> item;
        res += item;
        //std::cerr << "item: " << item;
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

std::string RequestHandler::getTextFileContent(std::string address)
{
    std::ifstream fileReader(address);
    std::string content;

    if(!fileReader.is_open())
    {
        content = "<!DOCTYPE html> <html lang=\"en\"> <body> <h1> HOME </h1> <p> 404 Error </p> </body> </html>";
        return content;
    }

    std::cerr << "File " << content << "\n";

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
}

std::string RequestHandler::getImageFileContent(std::string address)
{
    std::ifstream imgReader(address, std::ios::in | std::ios::binary);
    std::filebuf* pbuf = imgReader.rdbuf();

    //imgReader.seekg (0, std::ios::end);
    //int length = imgReader.tellg();
    //char* buffer = new char[BYTE_SIZE];
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(imgReader), {});
    
    std::cerr << "BUFFER OUTPUT HERE ";
    for(unsigned char u:buffer)
        std::cerr << u;
    std::cerr << "\n\n";
    std::cerr << "Image reader\n";

    if(imgReader.bad())
    {
        return "<!DOCTYPE html> <html lang=\"en\"> <body> <h1> HOME </h1> <p> 404 Error </p> </body> </html>";
    }

    std::string content{buffer.begin(), buffer.end()};
    //imgReader.read(buffer, length);
    imgReader.close();

    std::cerr << "BUFFER " << buffer.size() << " || ";
    std::cerr <<  content << "\n";
    //std::ofstream imgWriter("imageOut.jpg", std::ios::out | std::ios::binary);
    //imgWriter.write(buffer, length);
    //imgWriter.close();

    //delete buffer;
    return content;
}


