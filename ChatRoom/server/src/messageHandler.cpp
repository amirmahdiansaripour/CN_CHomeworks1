#include "../header/messageHandler.hpp"

using namespace std;

MessageHandler::MessageHandler(vector<User*> u){
    users = u;
}

string MessageHandler::handle(string request){
    return "Got your request!\n";
}