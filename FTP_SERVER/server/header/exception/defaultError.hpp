#ifndef _DEFAULT_ERROR_
#define _DEFAULT_ERROR_

#include <exception>
#include <string>
const int DEFAULT_ERROR_CODE = 500;
const std::string DEFAULT_ERROR_MESSAGE = std::to_string(DEFAULT_ERROR_CODE) + ": Error\n";

class DefaultError : public std::exception
{
public:
    ~DefaultError();
    const char* what() const throw();
};


#endif