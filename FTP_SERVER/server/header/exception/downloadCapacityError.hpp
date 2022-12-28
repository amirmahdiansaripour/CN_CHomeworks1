#ifndef _DOWNLOAD_CAPACITY_
#define _DOWNLOAD_CAPACITY_

#include <exception>
#include <string>
const int DOWNLOAD_CAPACITY_CODE = 425;
const std::string DOWNLOAD_CAPACITY_MESSAGE = std::to_string(DOWNLOAD_CAPACITY_CODE) + ": Can't open data connection.\n";

class DownloadCapacityError : public std::exception
{
public:
    ~DownloadCapacityError();
    const char* what() const throw();
};


#endif