#ifndef _REQUEST_HANDLER_
#define _REQUEST_HANDLER_

#include <string>


class RequestHandler
{
    public:
        RequestHandler();
        std::string handleGetRequest(std::string request);
    private:
        std::string getFileName(std::string response);
        std::string getTextFileContent(std::string address);
        std::string getFileType(std::string fileName);
        std::string fileResponse(std::string content, std::string contentType, bool redirect = false);
        std::string getBinaryFileContent(std::string address);
        std::string getContentType(std::string fileType);
        std::string getErrorFile();
        std::string redirectHeader(std::string newLocation);
        std::string redirectLocation;
};

#endif