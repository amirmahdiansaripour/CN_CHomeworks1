#include "../header/user.hpp"
#include <iostream>

using namespace std;

User::User(const string username_, const string password_, 
            int size, bool admin){
    username = username_;
    password = password_;
    maxDownloadSize = size;
    isAdmin = admin;
}

void User::printUserData(){
    cout << "username: " << username << "\n";
    cout << "password: " << password << "\n";
    cout << "downloadSize: " << maxDownloadSize << "\n";
    cout << "isAdmin: " << isAdmin << "\n";
    cout << "\n\n";
}

bool User::identicalUsername(string username_) {
    return username == username_;
}

bool User::isCorrectPassword(string inputPassword) {
    return inputPassword == password;
}