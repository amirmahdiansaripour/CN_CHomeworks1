#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "../header/user.hpp"
#include <string>
#include <vector>

#define USER_SIGNIN     "user"
#define PASS_SIGNIN     "pass"
#define HELP            "help"
#define QUIT            "quit"
#define DOWNLOAD        "retr"
#define DOWNLOAD_FOLDER " ../client/clientDownloads/"

class MessageHandler{
public:
    MessageHandler(std::vector<User*>);
    std::string handle(std::string);
    int loginUsername(std::string);
    int loginPassword(std::string);
    int clientQuit();
    int handleDownload(std::string);
private:
    int id;
    std::vector<User*> usersFromServer;
    User* incompleteUser;
    User* currentUser;
    bool userEntered;
    bool passEntered;    
    std::string currentDirectory;
};

#endif