#include "../../header/exception/notLoggedInError.hpp"

NotLoggedInError::~NotLoggedInError() {}

const char * NotLoggedInError::what() const throw()
{
    return NOT_LOGGED_IN_ERROR.c_str();
}