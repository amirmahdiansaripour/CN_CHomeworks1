#include "../header/messageHandler.hpp"
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

vector<string> parseMessage(string message) {
    stringstream sstream stringstream(message);
    vector<string> parsedMessage;
    string token;
    while (getline(sstream, token, ' '))
    {
        parsedMessage.push_back(token);
    }
    return parsedMessage;
}

MessageHandler::MessageHandler(int id_){
    id = id_;
}

string MessageHandler::handle(string message){

    vector<string> parsedMessage = parseMessage(message);
    string command = parsedMessage[0];
    try {
        if (command == USER_SIGNIN)
        {

        }
    }
    catch (Exception e) {

    }
    // response to each message is provided here.
    return NULL;
}

