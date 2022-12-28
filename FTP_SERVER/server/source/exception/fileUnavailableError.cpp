#include "../../header/exception/fileUnavailableError.hpp"

FileUnavailableError::~FileUnavailableError() {}

const char * FileUnavailableError::what() const throw()
{
    return FILE_UNAVAILABLE_MESSAGE.c_str();
}