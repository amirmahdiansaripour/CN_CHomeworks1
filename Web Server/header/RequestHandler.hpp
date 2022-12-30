#ifndef _REQUEST_HANDLER_
#define _REQUEST_HANDLER_

#include <string>
const std::string HOME_FILE = "home.html";
const std::string HTML = "html";
const std::string GIF = "gif";
const std::string MP3 = "mp3";
const std::string JPEG = "jpeg";
const std::string JPG = "jpg";
const std::string PDF = "pdf";

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
        std::string getImageFileContent(std::string address);
        std::string getContentType(std::string fileType);
};

#endif