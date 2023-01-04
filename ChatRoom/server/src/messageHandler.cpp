#include "../header/messageHandler.hpp"

using namespace std;



MessageHandler::MessageHandler(){
}

vector<User*> MessageHandler::getUsers(){
    return users;
}

// These two functions may change in the future

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
    cout << "res: " << res << "\n";
    return res;
}

/////////////////////

string MessageHandler::handle(string request){
    string reqType = request.substr(0, 4);
    if(reqType == CONNECT){
        return handleConnectReq(request);

    }
    else if(reqType == LIST){
        return handleListReq();
    }

    else if(reqType == INFO){
        return handleInfo(request);
    }

    else{
        return "Wrong input\n";
    }

}


string MessageHandler::handleConnectReq(string req){
    string userName = getPayLoad(req);
    // cout << "user: " << userName << "\n";
    User* newUser = new User(userName, users.size());
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
    cout <<"demandedID : " << demandedID << "\n";
    return users[demandedID]->getName();
}