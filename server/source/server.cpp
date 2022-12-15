#include "../header/server.hpp"
#include "../header/messageHandler.hpp"

using namespace std;

vector<User*> usersTosend;

Server::Server(const string path){
    configReader = ConfigReader(path);
    fileNames = configReader.getFilesNames();
    users = configReader.getUsers();

}

void error(const char *msg){
    perror(msg);
    exit(0);
}

struct threadArg{
    int threadID;
    int client;
};

typedef struct threadArg threadArg;

void* handleConnection(void* thread){
    threadArg *arg = (threadArg *) thread;
    MessageHandler* messageHandler = new MessageHandler(usersTosend);
    // cout << messageHandler->usersFromServer.size() << "gg\n";
    char readClient[1024];
    string sendClient;
    while(true){
        memset(readClient, 0, 1024);
        bzero(readClient, 1024);
        if(recv(arg->client, readClient, sizeof(readClient), 0) > 0){
            cout << "Client: " << string(readClient) << "\n";
            sendClient = messageHandler->handle(string(readClient));
            cout << "Server: " << sendClient << "\n";
        }
    }

}

void Server::run(){

    int serverFd = setupServer(8083);
    pthread_t threads[MAX_CLIENTS];  
    int numOfThreads = 0;
    usersTosend = users;
    while (true){
        int clientFd = acceptClient(serverFd);
        if(clientFd == -1)
            error("ERROR: could not accept client\n");
        
        threadArg arg;
        arg.client = clientFd;
        arg.threadID = numOfThreads;
        int result = pthread_create(&threads[numOfThreads], NULL, &handleConnection, (void*)& arg);
        if(result){
            error(("ERROR: could not create thread " + to_string(numOfThreads) + "\n").c_str());
        }
        numOfThreads++;
    }
    for(int i = 0; i < numOfThreads; i++){
        pthread_join(threads[i], NULL);
    }
    
}

int Server::setupServer(int port) 
{
    struct sockaddr_in address;
    int serverFd;

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    
    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(serverFd, (struct sockaddr*)& address, sizeof(address));

    listen(serverFd, 10);

    return serverFd;
}

int Server::acceptClient(int serverFd) 
{
    struct sockaddr_in clientAddress;
    int addressLen = sizeof(clientAddress);

    int clientFd = accept(serverFd, (struct sockaddr *)& clientAddress, (socklen_t*) &addressLen);

    return clientFd;
}