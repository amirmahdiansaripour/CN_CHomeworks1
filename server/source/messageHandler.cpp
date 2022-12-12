#include "../header/messageHandler.hpp"
#include "../header/reponse.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include <exception>
using namespace std;

vector<string> parseMessage(string message);

vector<string> parseMessage(string message) {
    stringstream sstream(message);
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
    Response response;
    try {
        if (command == USER_SIGNIN)
        {
            string username = parsedMessage[1];
            return response.getResponseMessage(handleUsername(username));
        }
    }
    catch (exception e) {

    }
    // response to each message is provided here.
    return NULL;
}