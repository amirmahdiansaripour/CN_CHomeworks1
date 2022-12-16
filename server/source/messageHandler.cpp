#include "../header/messageHandler.hpp"
#include "../header/response.hpp"
#include "../header/eventLogger.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>
using namespace std;

string downloadedFileContent;

string runCommandOnTerminal(string commandShell, vector<string> args);
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
    currentDirectory = runCommandOnTerminal("pwd", vector<string>{});
    // cout << "currentDirectory: " << currentDirectory;
}

string MessageHandler::handle(string message){

    vector<string> parsedMessage = parseMessage(message);
    string command = parsedMessage[0];
    Response response;
    // cout << "comm: " << command << "\n";
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
        else if(command == DOWNLOAD){
            string fileName_ = parsedMessage[1];
            int downloadRes = handleDownload(fileName_);
            return response.getResponseMessage(downloadRes);
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
        
        EventLogger::logUserLogin(currentUser);
        return SUCCESSFUL_LOGIN;
    }
    else {
        return INVALID_USER_PASS;
    }

}

int MessageHandler::clientQuit(){
    
    passEntered = false;
    EventLogger::logUserLogout(currentUser);
    currentUser = NULL;
    return QUIT_CODE;
}

int MessageHandler::handleDownload(string fileName){

    vector<string> terminalArg;
    terminalArg.push_back(fileName);
    runCommandOnTerminal("cd " + currentDirectory + " && cat ", terminalArg);
    EventLogger::logDownload(currentUser, fileName);
    return DOWNLOAD_CODE;
}

string runCommandOnTerminal(string commandShell, vector<string> args){
    char fileName[L_tmpnam];
    tmpnam(fileName);
    for(string argument : args)
        commandShell += (" " + argument);

    commandShell += " >> ";

    commandShell += fileName;
    system(commandShell.c_str());
    ifstream file(fileName);
    string fileContent;
    if(!file){
        perror("ERROR : could not open the file.\n");
        exit(0);
    }
    else{
        while(!file.eof()){
            fileContent += file.get();
        }
        file.close();
    }
    fileContent.pop_back();
    fileContent.pop_back();
    return fileContent;
}