#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "../header/user.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>
#include <algorithm>
#include <sys/stat.h>

#define USER_SIGNIN     "user"
#define PASS_SIGNIN     "pass"
#define HELP            "help"
#define QUIT            "quit"
#define DOWNLOAD        "retr"
#define UPLOAD          "upload"
#define DOWNLOAD_FOLDER " ../client/clientDownloads/"
#define UPLOAD_FOLDER " ../Files/"

const int MAX_FILE_SIZE = 1048576;  // Bytes

class MessageHandler{
public:
    MessageHandler(std::vector<User*>, std::vector<std::string>);
    std::string handle(std::string);
    int loginUsername(std::string);
    int loginPassword(std::string);
    int clientQuit();
    int handleDownload(std::string);
    int handleUpload(std::string);
private:
    int id;
    std::vector<User*> usersFromServer;
    std::vector<std::string> adminFiles;
    User* incompleteUser;
    User* currentUser;
    bool userEntered;
    bool loggedIn;
    bool passEntered;    
    std::string currentDirectory;
};

#endif