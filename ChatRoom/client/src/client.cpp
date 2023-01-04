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

vector<string> getNames(string unsplitted){
    
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

Client::Client(int port_, string name_){
    port = port_;
    name = name_;
    commandChannel = connectServer(port);
    sendInitData();
}

void Client::run()
{
    string request;    
    string sendToClient;
    char readFromServer[1024];
    while(getline(cin, request)) 
    {
        if(request == LISTCOMMAND){
            sendToClient = LIST + generateRandomString() + "2";
            send(commandChannel, sendToClient.c_str(), sendToClient.size(), 0);
            recv(commandChannel, readFromServer, sizeof(readFromServer), 0);
            // cout << "commandChannel: \n" << readFromServer << "\n";
            vector<string> splittedData = getNames(readFromServer);
            for(string s : splittedData)
                cout << "- " << s << "\n";
        
        }
        // cout << "commandChannel: \n" << readFromServer << "\n";
        // if(needDataChannel(readFromServer)){
        //     recv(dataChannel, readFromServer, sizeof(readFromServer), 0);
        //     cout << "dataChannel: \n" << readFromServer << "\n";
        // }
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