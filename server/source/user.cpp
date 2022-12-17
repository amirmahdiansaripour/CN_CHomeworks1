#include "../header/user.hpp"
#include <iostream>

using namespace std;

User::User(string username_, string password_, 
            int size, bool admin){
    username = username_;
    password = password_;
    maxDownloadSize = size;
    isAdmin = admin;
}

bool User::getAdmin(){return isAdmin;}

void User::printUserData(){
    cout << "username: " << username << "\n";
    cout << "password: " << password << "\n";
    cout << "downloadSize: " << maxDownloadSize << "\n";
    cout << "isAdmin: " << isAdmin << "\n";
    cout << "\n\n";
}

bool User::handleCapacity(int fileToDownloadSize){
    // cout << "maxCapacity: " << maxDownloadSize << "\n";
    if(fileToDownloadSize > maxDownloadSize){
        return false;
    }
    else{
        maxDownloadSize -= fileToDownloadSize;
        // cout << "fileSize: " << fileToDownloadSize << "\n";
        // cout << "maxCapacity: " << maxDownloadSize << "\n";
        return true;
    }
}

bool User::identicalUsername(string username_) {
    return username == username_;
}

bool User::isCorrectPassword(string inputPassword) {
    return inputPassword == password;
}

std::string User::getUsername()
{
    return username;
}