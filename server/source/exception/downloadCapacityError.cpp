#include "../../header/exception/downloadCapacityError.hpp"

DownloadCapacityError::~DownloadCapacityError() {}

const char * DownloadCapacityError::what() const throw()
{
    return DOWNLOAD_CAPACITY_MESSAGE.c_str();
}