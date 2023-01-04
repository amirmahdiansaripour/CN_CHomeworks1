
#include "../header/server.hpp"
#include "../header/messageHandler.hpp"
#include "../header/user.hpp"

using namespace std;

void error(const char *msg){
    perror(msg);
    exit(0);
}

Server::Server(){
}

struct threadArg{
    int clientChannel;
    int clientID;
}arg;

MessageHandler* messageHandler = new MessageHandler();


void* handleConnection(void* thread){
    threadArg *currArg = (threadArg *) thread;
    //  cerr << "argument commandFd " << currArg->clientChannel << "\n";
    //  cerr << "argument datafd" << currArg->dataChannel << "\n";
    char readClient[1024];
    string sendClient;
    while(true){
        memset(readClient, 0, 1024);
        bzero(readClient, 1024);
        bool dchanel;
        if(recv(currArg->clientChannel, readClient, sizeof(readClient), 0) > 0){
            cout << "Client: " << string(readClient) << "\n";
            sendClient = messageHandler->handle(string(readClient));





        }
        else{
            error("ERROR: could not receive from client\n");
        }
        send(currArg->clientChannel, sendClient.c_str(), sizeof(readClient), 0);
        
    }

}

void Server::run(){
    int fd = setupServer(PORT);
    pthread_t threads[MAX_CLIENTS];  
    threadArg clientArg[MAX_CLIENTS];
    int numOfThreads = 0;
    while (true){
        int clientFd = acceptClient(fd);
        // cout << "clientFd: " << clientFd << "\n";
        if(clientFd == -1)
            error("ERROR: could not accept client\n");
        
        clientArg[numOfThreads].clientChannel = clientFd;
        clientArg[numOfThreads].clientID = numOfThreads;
        int result = pthread_create(&threads[numOfThreads], NULL, &handleConnection, (void*)& clientArg[numOfThreads]);
        if(result){
            error(("ERROR: could not create thread " + to_string(numOfThreads) + "th\n").c_str());
        }
        numOfThreads++;
    }
    for(int i = 0; i < numOfThreads; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_exit(NULL);

}


int Server::setupServer(int port_){
    struct sockaddr_in address;
    int serverFd;

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    
    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    bind(serverFd, (struct sockaddr*)& address, sizeof(address));

    listen(serverFd, 10);

    return serverFd;

}

int Server::acceptClient(int serverFd) {
    struct sockaddr_in clientAddress;
    int addressLen = sizeof(clientAddress);

    int clientFd = accept(serverFd, (struct sockaddr *)& clientAddress, (socklen_t*) &addressLen);

    return clientFd;
}