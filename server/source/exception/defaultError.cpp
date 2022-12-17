#include "../../header/exception/defaultError.hpp"

DefaultError::~DefaultError() {}

const char * DefaultError::what() const throw()
{
    return DEFAULT_ERROR_MESSAGE.c_str();
}