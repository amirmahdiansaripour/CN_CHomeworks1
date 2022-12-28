#include "../header/messageHandler.hpp"
#include "../header/response.hpp"
#include "../header/eventLogger.hpp"

#include "../header/exception/badSequenceError.hpp"
#include "../header/exception/defaultError.hpp"
#include "../header/exception/downloadCapacityError.hpp"
#include "../header/exception/fileUnavailableError.hpp"
#include "../header/exception/invalidUserPassError.hpp"
#include "../header/exception/notLoggedInError.hpp"
#include "../header/exception/syntaxError.hpp"

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
        exception* ex = new SyntaxError();
        throw ex;
    }

    while(!myfile.eof()){
        fileContent += myfile.get();
    }
    myfile.close();

    fileContent.pop_back();
    fileContent.pop_back();
    return fileContent;
}

string getCurrentDir(){
    char tmpFile[L_tmpnam];
    tmpnam(tmpFile);
    runCommandOnTerminal("pwd", "", tmpFile);
    string result = getFileContent(tmpFile);
    return result;
}

MessageHandler::MessageHandler(vector<User*> users, vector<string> adminFiles_){
    usersFromServer = users;
    userEntered = false;
    passEntered = false;
    loggedIn = false;
    incompleteUser = NULL;
    currentUser = NULL;
    currentDirectory = getCurrentDir();
    adminFiles = adminFiles_;
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
            if(!loggedIn){
                exception* ex = new NotLoggedInError();
                throw ex;
            }
            return response.getResponseMessage(HELP_CODE);
        }
        else if(command == QUIT){
            
            int quitRes = clientQuit();
            return response.getResponseMessage(quitRes);
        }
        else if(command == DOWNLOAD){
            downloadedFileContent = "";
            string fileName_ = parsedMessage[1];
            int downloadRes = handleDownload(fileName_);
            return (downloadedFileContent + response.getResponseMessage(downloadRes));
        }

        else if(command == UPLOAD){
            uploadedFileContent = "";
            string fileName_ = parsedMessage[1];
            int upLoadRes = handleUpload(fileName_);
            return (uploadedFileContent + response.getResponseMessage(upLoadRes));
        }

        else{
            exception* ex = new SyntaxError();
            throw ex;
        }

    }
    catch (exception* e) {
        string ret = string(e->what());
        delete e;
        return ret;
    }
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
    exception* e = new InvalidUserPassError();
    throw e;
}

int MessageHandler::loginPassword(string password) 
{
    if(!userEntered) {  // Bad sequence
        exception* ex = new BadSequenceError();
        throw ex;
    }
    
    else if(incompleteUser->isCorrectPassword(password)) {
        userEntered = false;
        passEntered = true;
        currentUser = incompleteUser;
        loggedIn = true;
        incompleteUser = NULL;
        
        EventLogger::logUserLogin(currentUser);
        return SUCCESSFUL_LOGIN;
    }
    else {
        exception* ex = new InvalidUserPassError();
        throw ex;
    }

}

int MessageHandler::clientQuit(){
    if(!loggedIn)
    {
        exception* ex = new NotLoggedInError();
        throw ex;
    }
    passEntered = false;
    userEntered = false;
    loggedIn = false;
    EventLogger::logUserLogout(currentUser);
    currentUser = NULL;
    return QUIT_CODE;
}

string getLastPartOfPath(string str){
    size_t found;
    found = str.find_last_of('/');
    if(found == string::npos) return str;
    else{
        string result = str.substr(found + 1); 
        return result;
    }
}

int getFileSizeBytes(string filePath){
    struct stat stat_buf;
    int rc = stat(filePath.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

int MessageHandler::handleDownload(string fileName){

    if(!loggedIn)
    {
        exception* ex = new NotLoggedInError();
        throw ex;
    }

    int fileSize = getFileSizeBytes(currentDirectory + "/" + fileName);
    
    bool allowedToDownload = currentUser->handleCapacity(fileSize);
    
    if(!allowedToDownload){
        exception* e = new DownloadCapacityError();
        throw e;
    }

    string res = getLastPartOfPath(fileName);   // ../server/test.txt => test.txt
    if(currentUser->getAdmin() == false && find(adminFiles.begin(), adminFiles.end(), fileName) != adminFiles.end()){
        exception* e = new FileUnavailableError();
        throw e;
    }
    string downloadPath = (DOWNLOAD_FOLDER + res);
    runCommandOnTerminal("cd " + currentDirectory + " && cat ", fileName, downloadPath);
    downloadedFileContent = (getFileContent(fileName) + "\n");
    EventLogger::logDownload(currentUser, fileName);
    return DOWNLOAD_CODE;
}

// Some differences exist between upload and download, implemented later.

int MessageHandler::handleUpload(string fileName){
    if(!loggedIn)
    {
        exception* ex = new NotLoggedInError();
        throw ex;
    }
    if(currentUser->getAdmin() == false){
        exception* e = new FileUnavailableError();
        throw e;
    }
    string res = getLastPartOfPath(fileName);
    string uploadPath = (UPLOAD_FOLDER + res);
    runCommandOnTerminal("cd " + currentDirectory + " && cat ", fileName, uploadPath);
    uploadedFileContent = (getFileContent(fileName) + "\n");
    EventLogger::logUpload(currentUser, fileName);
    return UPLOAD_CODE;
}
