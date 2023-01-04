#include "../header/client.hpp"

using namespace std;

void error(const char *msg){
    perror(msg);
    exit(0);
}


Client::Client(int port_){
    port = port_;
}

void Client::run()
{
    string request;    
    
    int commandChannel = connectServer(port);
    char readFromServer[1024];
    while(getline(cin, request)) 
    {
        // getline(cin, request);
        send(commandChannel, request.c_str(), request.size(), 0);
        recv(commandChannel, readFromServer, sizeof(readFromServer), 0);
        cout << "commandChannel: \n" << readFromServer << "\n";
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