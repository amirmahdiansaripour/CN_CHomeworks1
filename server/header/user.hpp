#ifndef __USER_H__
#define __USER_H__

#include <string>

class User{
public:
    User(std::string, std::string, int, bool);
    void printUserData();
    bool identicalUsername(std::string username_);
    std::string getUsername();
    bool isCorrectPassword(std::string inputPassword);
private:
    std::string username;
    std::string password;
    int maxDownloadSize;
    bool isAdmin;
};

#endif