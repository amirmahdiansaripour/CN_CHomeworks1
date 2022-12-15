#include "../header/messageHandler.hpp"
#include "../header/response.hpp"
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
            return response.getResponseMessage(loginUsername(username));
        }
        else if (command == PASS_SIGNIN) 
        {
            string password = parsedMessage[1];
            return response.getResponseMessage(loginPassword(password));
        }
    }
    catch (exception e) {

    }
    // response to each message is provided here.
    return NULL;
}

int MessageHandler::loginUsername(string username) 
{
    for(User u: users) 
    {
        if(u.identicalUsername(username)) {
            return USERNAME_FOUND;
        }
    }
    return INVALID_USER_PASS;
}

int MessageHandler::loginPassword(string password) 
{
    if(!incompleteLogin) {
        return PASS_WITHOUT_USER;
    }
    
    else if(incompleteLoginUser->isCorrectPassword(password)) {
        incompleteLogin = false;
        loggedIn = true;
        currentUser = incompleteLoginUser;
        incompleteLoginUser = nullptr;
        return SUCCESSFUL_LOGIN;
    }
    else {
        return INVALID_USER_PASS;
    }

}