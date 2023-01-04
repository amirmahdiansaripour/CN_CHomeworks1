#include "../header/user.hpp"

using namespace std;

User::User(string name_, int id_){
    id = id_;
    name = name_;
}

int User::getID(){
    return id;
}

string User::getName(){
    return name;
}