#include "../header/messageHandler.hpp"

using namespace std;



MessageHandler::MessageHandler(){
}

// These two functions may change in the future

vector<string> split(string unsplitted){    
    stringstream ss(unsplitted);
    vector<string> v;
    while (getline(ss, unsplitted, ' ')) {
        v.push_back(unsplitted);
    }
    vector<string>::iterator it;
    it = v.begin();
    v.erase(it);
    return v;
}

string getPayLoad(string in){
    int charIndex = in.size() - 1;
    // cout << "charIndex: " << charIndex << "\n";
    while(isalpha(in[charIndex])){
        charIndex--;
    }
    return in.substr(charIndex + 1, in.size());
}

string generateRandomString(){
    srand((unsigned) time(NULL));
    int random = rand() % 16;
    return messageID[random];
}

string getUserIDInfoReq(string req){
    string res = req.substr(9, req.size()); 
    return res;
}

/////////////////////

string MessageHandler::handle(string request, int clientFd_){
    string reqType = request.substr(0, 4);
    clientFd = clientFd_;
    if(reqType == CONNECT){
        return handleConnectReq(request, clientFd_);

    }
    else if(reqType == LIST){
        return handleListReq();
    }

    else if(reqType == INFO){
        return handleInfo(request);
    }

    else if(reqType == SEND){
        vector<string> splitted = split(request);
        return handleSend(splitted);
    }

    else if(reqType == RECEIVE){
        return handleReceive();
    }

    else{
        return "Wrong input\n";
    }

}


User* MessageHandler::findSender(){
    for(User* u : users){
        if(u->getChannel() == clientFd){
            return u;
        }
    }
}

string MessageHandler::handleConnectReq(string req, int clientFd){
    string userName = getPayLoad(req);
    // cout << "user:" << userName << "\n";
    User* newUser = new User(userName, users.size(), clientFd);
    users.push_back(newUser);
    
    return CONNACK + generateRandomString() + "2";
}


string MessageHandler::handleListReq(){
    vector<string> usersID;
    int messageLen = 2 + 2*users.size();
    // cout << "users.size() : " << users.size() << "\n";
    string res = LISTREPLY + generateRandomString() + to_string(messageLen);
    for(User* u : users){
        usersID.push_back(u->getName());
    }
    for(string s : usersID){
        res += (" " +  s);
    }
    return res;
}


string MessageHandler::handleInfo(string request){
    int demandedID = stoi(getUserIDInfoReq(request));
    string res = INFOREPLY + generateRandomString();

    if(demandedID >= users.size())
        res += "2";
    
    else{
        string demandedName = users[demandedID]->getName();
        int messageLen = 2 + demandedName.size();
        res += to_string(messageLen);
        res += (" " + demandedName);
    }
    return res;
}

string MessageHandler::handleSend(vector<string>args){
    string receiverName = args[0];
    int status = 0;
    string res;
    for(User* u : users){
        if(u->getName() == receiverName){
            u->addToArchive({findSender()->getName(), args[1]});
            status = 1;
        }
    }
    res = SENDREPLY + generateRandomString() + "3" + to_string(status);
    return res;
}

string MessageHandler::handleReceive(){
    vector<string> archiveMessages = findSender()->getArchivedMessages();
    string res;
    int messageLen = 2;
    for(int i = 0; i < archiveMessages.size(); i++){
        res += (archiveMessages[i] + " ");
        if(i % 2 == 1){
            messageLen += archiveMessages[i].size();
        }
    }
    if(archiveMessages.size() > 0){
        return RECEIVEREPLY + generateRandomString() + to_string(messageLen) + " " + res;
    }
    else{
        return RECEIVEREPLY + generateRandomString() + to_string(messageLen) + "0";
    }
}