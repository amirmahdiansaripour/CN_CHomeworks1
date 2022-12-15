#include "../header/server.hpp"
#include "../header/messageHandler.hpp"

using namespace std;

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
    int commandID;
    int dataID;
};
typedef struct threadArg threadArg;

void* handleConnection(int commandID, int dataID){
    // threadArg *arg = (threadArg *) threadArgs;
    MessageHandler* messageHandler = new MessageHandler(dataID);
    char read_buffer[1024];
    string send_buffer;
    while(true){
        memset(read_buffer, 0, 1024);
        bzero(read_buffer, 1024);
        if(recv(commandID, read_buffer, sizeof(read_buffer), 0) > 0){
            cout << "Client: " << string(read_buffer) << "\n";
            send_buffer = messageHandler->handle(string(read_buffer));
            cout << "Server: " << send_buffer << "\n";
            pthread_exit(NULL);
        }
        pthread_exit(NULL);
    }

}

void Server::run(){
    int dataFd = setupServer(8082);
    int commandFd = setupServer(8083);
    pthread_t threads[1024];
    int numOfThreads = 0;
    while (true){
        int newCommand = acceptClient(commandFd);
        int newData = acceptClient(dataFd);
        if(newCommand == -1 || newData == -1)
            error("ERROR: could not accept client\n");
        
        threadArg arg;
        arg.commandID = newCommand;
        arg.dataID = newData;
        arg.threadID = numOfThreads;
        handleConnection(arg.commandID, arg.dataID);
        // int result = pthread_create(&threads[numOfThreads], NULL, &handleConnection, (void*)& arg);
        // if(result){
        //     error(("ERROR: could not create thread " + to_string(numOfThreads) + "\n").c_str());
        // }
        numOfThreads++;
    }
    // for(int i = 0; i < numOfThreads; i++){
    //     pthread_join(threads[i], NULL);
    // }
    
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