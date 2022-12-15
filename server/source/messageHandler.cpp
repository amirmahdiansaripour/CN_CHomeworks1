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

MessageHandler::MessageHandler(vector<User*> users){
    usersFromServer = users;
    userEntered = false;
    passEntered = false;
    incompleteUser = NULL;
    currentUser = NULL;

}

string MessageHandler::handle(string message){

    vector<string> parsedMessage = parseMessage(message);
    string command = parsedMessage[0];
    Response response;
    try {
        if (command == USER_SIGNIN)
        {
            string username = parsedMessage[1];
            string sendToClient = string(response.getResponseMessage(loginUsername(username)));
            return sendToClient;
        }
        else if (command == PASS_SIGNIN) 
        {
            string password = parsedMessage[1];
            return response.getResponseMessage(loginPassword(password));
        }
        else if(command == HELP){
            return response.getResponseMessage(HELP_CODE);
        }
        else if(command == QUIT){
            int quitRes = clientQuit();
            return response.getResponseMessage(quitRes);
        }
    }
    catch (exception e) {

    }
    // response to each message is provided here.
    return NULL;
}

int MessageHandler::loginUsername(string username) 
{
    for(User* u: usersFromServer) 
    {
        if(u->identicalUsername(username)) {
            incompleteUser = u;
            userEntered = true;
            return USERNAME_FOUND;
        }
    }
    return INVALID_USER_PASS;
}

int MessageHandler::loginPassword(string password) 
{
    if(!userEntered) {  // Bad sequence
        return PASS_WITHOUT_USER;
    }
    
    else if(incompleteUser->isCorrectPassword(password)) {
        userEntered = false;
        passEntered = true;
        currentUser = incompleteUser;
        incompleteUser = NULL;
        return SUCCESSFUL_LOGIN;
    }
    else {
        return INVALID_USER_PASS;
    }

}

int MessageHandler::clientQuit(){
    

    return QUIT_CODE;
}

