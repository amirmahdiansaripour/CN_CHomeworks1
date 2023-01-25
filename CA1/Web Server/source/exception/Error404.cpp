#include "../../header/exception/Error404.hpp"
#include <fstream>
#include <iostream>

Error404::~Error404() {}

const char * Error404::what() const throw()
{
    return "Error 404 : file not found\n";
}


