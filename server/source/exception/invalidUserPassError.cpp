#include "../../header/exception/invalidUserPassError.hpp"

#include <iostream>
InvalidUserPassError::~InvalidUserPassError() {}

const char* InvalidUserPassError::what() const throw()
{
    return INVALID_USER_PASS_MESSAGE.c_str();
}