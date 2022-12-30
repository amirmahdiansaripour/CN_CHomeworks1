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
        std::string fileResponse(std::string content, std::string contentType);
        std::string getBinaryFileContent(std::string address);
        std::string getContentType(std::string fileType);
        std::string getErrorFile();
};

#endif