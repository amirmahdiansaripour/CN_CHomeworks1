#include "../header/client.hpp"

using namespace std;

void error(const char *msg){
    perror(msg);
    exit(0);
}

string generateRandomString(){
    srand((unsigned) time(NULL));
    int random = rand() % 16;
    return messageID[random];
}

void Client::sendInitData(){
    char readFromServer[1024];
    int messageSize = 2 + name.size();
    string message = CONNECT + generateRandomString() + to_string(messageSize) + name;
    send(commandChannel, message.c_str(), message.size(), 0);
    recv(commandChannel, readFromServer, sizeof(readFromServer), 0);
    // cout << "commandChannel: \n" << readFromServer << "\n";
}

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

void printList(string readFromServer){
    vector<string> splittedData = split(readFromServer);
    for(string s : splittedData)
    cout << "- " << s << "\n";    
}

Client::Client(int port_, string name_){
    port = port_;
    name = name_;
    commandChannel = connectServer(port);
    sendInitData();
}


void Client::listReq(string request){
    string sendToServer;
    char readFromServer[1024];
    sendToServer = LIST + generateRandomString() + "2";
    send(commandChannel, sendToServer.c_str(), sendToServer.size(), 0);
    recv(commandChannel, readFromServer, sizeof(readFromServer), 0);
    printList(readFromServer);
}

void Client::infoReq(string request){
    string sendToServer;
    char readFromServer[1024];
    sendToServer = INFO + generateRandomString() + "4" + request.substr(5, request.size());
    send(commandChannel, sendToServer.c_str(), sendToServer.size(), 0);
    recv(commandChannel, readFromServer, sizeof(readFromServer), 0);
    if(string(readFromServer).find(" ") == string::npos){
        cout << "-Payload is empty\n";
    }
    else{
        printList(readFromServer);
    }
}

void Client::receiveReq(string request){
    string sendToServer;
    char readFromServer[1024];
    sendToServer = RECEIVE + generateRandomString() + "2";
    send(commandChannel, sendToServer.c_str(), sendToServer.size(), 0);
    recv(commandChannel, readFromServer, sizeof(readFromServer), 0);
    vector<string>splitted =  split(readFromServer);
    if(splitted.size() == 0 && string(readFromServer).back() == '0'){
        cout << "-Payload is empty\n";
    }
    else{
        for(int i = 0; i < splitted.size() - 1; i += 2)
            cout << "- " << splitted[i] << ": " << splitted[i + 1] << "\n";
    }
}

void Client::sendReq(string request){
    string sendToServer;
    char readFromServer[1024];
    vector<string> splitted = split(request);
    int messageLen = 4 + splitted[1].size();
    sendToServer = (SEND + generateRandomString() + to_string(messageLen)  + " " + splitted[0] + " " + splitted[1]);
    send(commandChannel, sendToServer.c_str(), sendToServer.size(), 0);
    recv(commandChannel, readFromServer, sizeof(readFromServer), 0);
    if(string(readFromServer).back() == '1'){
        cout << "success\n";
    }            
    else{
        cout << "failure\n";
    }
}

void Client::quitReq(){
    string sendToServer = QUITCOMMAND;
    char readFromServer[1024];
    
    send(commandChannel, sendToServer.c_str(), sendToServer.size(), 0);
    recv(commandChannel, readFromServer, sizeof(readFromServer), 0);
    cout << readFromServer << "\n";
}

void Client::run()
{
    string request;    
    
    while(getline(cin, request)) 
    {
        if(request == QUITCOMMAND){
            quitReq();
        }

        if(request == LISTCOMMAND){
            listReq(request);
        }

        else if(request.substr(0, 4) == INFOCOMMAND){
            infoReq(request);
        }

        else if(request == RECEIVECOMMAND){
            receiveReq(request);
        }

        else if(request.substr(0, 4) == SENDCOMMAND){
            sendReq(request);
        }


    }



}

int Client::connectServer(int port) 
{
    int socket_fd;
    struct sockaddr_in serverAddress;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) 
        error("ERROR : could not make a socket\n");
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(socket_fd, (struct sockaddr *)& serverAddress, sizeof(serverAddress)) < 0){
        error("ERROR : could not connect\n");
    }
    
    return socket_fd;

}