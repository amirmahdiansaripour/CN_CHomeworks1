#ifndef _SYNTAX_ERROR_
#define _SYNTAX_ERROR_

#include <exception>
#include <string>
const int SYNTAX_ERROR_CODE = 501;
const std::string SYNTAX_ERROR_MESSAGE = std::to_string(SYNTAX_ERROR_CODE) + ": Syntax error in parameters or arguments.\n";

class SyntaxError : public std::exception
{
public:
    ~SyntaxError();
    const char* what() const throw();
};


#endif