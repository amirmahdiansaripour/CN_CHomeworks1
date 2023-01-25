#ifndef _FILE_UNAVAILABLE_ERROR_
#define _FILE_UNAVAILABLE_ERROR_

#include <exception>
#include <string>
const int FILE_UNAVAILABLE_CODE = 550;
const std::string FILE_UNAVAILABLE_MESSAGE = std::to_string(FILE_UNAVAILABLE_CODE) + ": File unavailable.\n";

class FileUnavailableError : public std::exception
{
public:
    ~FileUnavailableError();
    const char* what() const throw();
};


#endif