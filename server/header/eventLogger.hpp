#ifndef _EVENT_LOGGER__
#define _EVENT_LOGGER__

#include <ctime>
#include "user.hpp"
#include <fstream>
#include <string>

const std::string LOG_FILE_PATH = "../log.txt";

class EventLogger 
{
public:
    EventLogger();
    static void logUserLogin(User* user);
    static void logDownload(User* user, std::string fileName);
    static void logUpload(User* user, std::string fileName);
    static void logUserLogout(User* user);
private:
    static void write(std::string text);
    static std::time_t getTime();
};


#endif