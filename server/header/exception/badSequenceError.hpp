#ifndef _BAD_SEQUENCE_H_
#define _BAD_SEQUENCE_H_

#include <exception>
#include <string>
const int BAD_SEQUENCE_CODE = 503;
const std::string BAD_SEQUENCE_MESSAGE = std::to_string(BAD_SEQUENCE_CODE) + ": Bad sequence of commands.\n";

class BadSequenceError : public std::exception
{
public:
    ~BadSequenceError();
    const char* what() const throw();
};


#endif