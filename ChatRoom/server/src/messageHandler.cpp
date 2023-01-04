#include "../header/messageHandler.hpp"

using namespace std;



MessageHandler::MessageHandler(vector<User*> u, int clientID){
    users = u;
    thisClient = clientID;
}

// These two functions may change in the future

string getPayLoad(string in){
    int charIndex = in.size() - 1;
    // cout << "charIndex: " << charIndex << "\n";
    while(isalpha(in[charIndex])){
        charIndex--;
    }
    return in.substr(charIndex + 1, in.size() - 1);
}

string generateRandomString(){
    srand((unsigned) time(NULL));
    int random = rand() % 16;
    return messageID[random];
}

/////////////////////

string MessageHandler::handle(string request){
    string reqType = request.substr(0, 4);
    if(reqType == CONNECT){
        return handleConnectReq(request);

    }
    

}


string MessageHandler::handleConnectReq(string req){
    string userName = getPayLoad(req);
    cout << "user: " << userName << "\n";
    User* newUser = new User(userName, thisClient);
    users.push_back(newUser);
    
    return CONNACK + generateRandomString() + "2";
}