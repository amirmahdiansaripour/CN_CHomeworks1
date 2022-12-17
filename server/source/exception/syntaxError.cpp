#include "../../header/exception/syntaxError.hpp"

SyntaxError::~SyntaxError(){}

const char * SyntaxError::what() const throw()
{
    return SYNTAX_ERROR_MESSAGE.c_str();
}