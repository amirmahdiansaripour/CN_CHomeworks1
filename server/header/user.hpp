#ifndef USER_H
#define USER_H

#include <string>

class User{
public:
    User(const std::string username,
        const std::string password);
private:
    std::string username;
    std::string password;
};

#endif