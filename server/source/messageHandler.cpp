#include "../header/messageHandler.hpp"
#include "../header/response.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>
using namespace std;

string downloadedFileContent;
string uploadedFileContent;

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

void runCommandOnTerminal(string commandShell, string fileToUpload, string fileToWrite){

    commandShell += (" " + fileToUpload);

    commandShell += " >> ";

    commandShell += fileToWrite;

    system(commandShell.c_str());
}

string getFileContent(string address){
    ifstream myfile;
    myfile.open(address);
    string fileContent;

    if(!myfile.is_open()){
        perror("ERROR: could not open file!\n");
        exit(0);
    }

    while(!myfile.eof()){
        fileContent += myfile.get();
    }
    myfile.close();

    fileContent.pop_back();
    fileContent.pop_back();
    // cout << "fileContent: " << fileContent << "\n";
    return fileContent;
}

string getCurrentDir(){
    char tmpFile[L_tmpnam];
    tmpnam(tmpFile);
    runCommandOnTerminal("pwd", "", tmpFile);
    string result = getFileContent(tmpFile);
    return result;
}

MessageHandler::MessageHandler(vector<User*> users){
    usersFromServer = users;
    userEntered = false;
    passEntered = false;
    incompleteUser = NULL;
    currentUser = NULL;
    currentDirectory = getCurrentDir();
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
        else if(command == DOWNLOAD){
            string fileName_ = parsedMessage[1];
            int downloadRes = handleDownload(fileName_);
            return (downloadedFileContent + response.getResponseMessage(downloadRes));
        }

        else if(command == UPLOAD){
            string fileName_ = parsedMessage[1];
            int upLoadRes = handleUpload(fileName_);
            return (uploadedFileContent + response.getResponseMessage(upLoadRes));
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
    
    passEntered = false;
    currentUser = NULL;
    return QUIT_CODE;
}

string getLastPartOfPath(string str){
    size_t found;
    found = str.find_last_of('/');
    if(found == string::npos) return str;
    else{
        string result = str.substr(found + 1); 
        // cout<< result << "\n";
        return result;
    }
}

int MessageHandler::handleDownload(string fileName){
    string res = getLastPartOfPath(fileName);   // ../server/test.txt => test.txt

    string downloadPath = (DOWNLOAD_FOLDER + res);
    runCommandOnTerminal("cd " + currentDirectory + " && cat ", fileName, downloadPath);
    downloadedFileContent = (getFileContent(fileName) + "\n");
    return DOWNLOAD_CODE;
}

// Some differences exist between upload and download, implemented later.

int MessageHandler::handleUpload(string fileName){
    string res = getLastPartOfPath(fileName);
    string uploadPath = (UPLOAD_FOLDER + res);
    runCommandOnTerminal("cd " + currentDirectory + " && cat ", fileName, uploadPath);
    uploadedFileContent = (getFileContent(fileName) + "\n");
    return UPLOAD_CODE;
}
