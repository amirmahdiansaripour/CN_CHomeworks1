#ifndef _404_ERROR_
#define _404_ERROR_

#include <exception>
#include <string>


class Error404 : public std::exception 
{
    public:
        ~Error404();
    private:
        const char* what() const throw();
};

#endif