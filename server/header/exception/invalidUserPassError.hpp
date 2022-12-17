#ifndef _INVALID_USER_PASS_ERROR_
#define _INVALID_USER_PASS_ERROR_

#include <exception>
#include <string>
const int INVALID_USER_PASS_CODE = 430;
const std::string INVALID_USER_PASS_MESSAGE = std::to_string(INVALID_USER_PASS_CODE )+ ": Invalid username or password\n";

class InvalidUserPassError : public std::exception
{
public:
    ~InvalidUserPassError();
    const char* what() const throw();
};


#endif


