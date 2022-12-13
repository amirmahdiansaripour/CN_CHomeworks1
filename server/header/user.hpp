#ifndef USER_H
#define USER_H

#include <string>

class User{
public:
    User(std::string, std::string, int, bool);
    void printUserData();
    bool identicalUsername(std::string username_);
    bool isCorrectPassword(std::string inputPassword);
private:
    std::string username;
    std::string password;
    int maxDownloadSize;
    bool isAdmin;
};

#endif