#ifndef _NOT_LOGGED_IN_
#define _NOT_LOGGED_IN_

#include <exception>
#include <string>
const int NEED_LOGIN = 332;
const std::string NOT_LOGGED_IN_ERROR = std::to_string(NEED_LOGIN) + ": Need account for login.\n";

class NotLoggedInError : public std::exception
{
public:
    ~NotLoggedInError();
    const char* what() const throw();
};


#endif