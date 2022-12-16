#include "../header/eventLogger.hpp"

EventLogger::EventLogger() 
{

}

void EventLogger::logUserLogin(User* user) 
{
    std::time_t eventTime = getTime();
    std::string log = user->getUsername() + " logged in at " + std::ctime(&eventTime);
    write(log);
}


void EventLogger::logUserLogout(User* user) 
{
    std::time_t eventTime = getTime();
    std::string log = user->getUsername() + " logged out at " + std::ctime(&eventTime);
    write(log);
}

void EventLogger::logDownload(User* user, std::string fileName) 
{
    std::time_t eventTime = getTime();
    std::string log = user->getUsername() + " downloaded file named " + fileName + " at " + std::ctime(&eventTime);
    write(log);
}


void EventLogger::logUpload(User* user, std::string fileName) 
{
    std::time_t eventTime = getTime();
    std::string log = user->getUsername() + " uploaded file named " + fileName + " at " + std::ctime(&eventTime);
    write(log);
}


void EventLogger::write(std::string text)
{
    std::ofstream logStream("log.txt", std::ios::app);
    logStream << text << "\n";
    logStream.close();

}

std::time_t EventLogger::getTime()
{
    std::time_t eventTime;
    std::time(&eventTime);
    return eventTime;
}