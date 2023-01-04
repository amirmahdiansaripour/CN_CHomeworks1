#include "../header/user.hpp"

using namespace std;

User::User(string name_, int id_, int channel_){
    id = id_;
    name = name_;
    channel = channel_;
}

int User::getChannel(){
    return channel;
}

int User::getID(){
    return id;
}

void User::addToArchive(string message){
    archiveMessages.push_back(message);
}

string User::getName(){
    return name;
}