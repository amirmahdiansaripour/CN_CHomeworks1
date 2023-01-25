#include "../../header/exception/badSequenceError.hpp"

BadSequenceError::~BadSequenceError() {}

const char* BadSequenceError::what() const throw()
{
    return BAD_SEQUENCE_MESSAGE.c_str();
}