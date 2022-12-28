#include "../header/server.hpp"
#include "../header/messageHandler.hpp"

using namespace std;

vector<User*> usersTosend;
vector<string> adminFilesToSend;

Server::Server(const string path){
    configReader = ConfigReader(path);
    adminFiles = configReader.getAdminFiles();
    adminFilesToSend = adminFiles;
    
    users = configReader.getUsers();
    commandPort = configReader.getCommandChannel();
    dataPort = configReader.getDataChannel();
    // cout << "commandPort: " << commandPort << "\n";
    // cout << "dataPort: " << dataPort << "\n";
}

void error(const char *msg){
    perror(msg);
    exit(0);
}

struct threadArg{
    int commandChannel;
    int dataChannel;
}arg;

bool needDataChannel(string sendToClient){
    if(sendToClient == "") return false;
    // cout << "sendToClient: \n";
    // cout << sendToClient;
    size_t found = sendToClient.find("Successful Download.");
    if(found != string::npos)   return true;
    else return false;
}

vector<string> splitCommandData(string mixedMessage){
    size_t found = mixedMessage.find("226: Successful Download.");
    string commandChannel = mixedMessage.substr(found);
    string dataChannel = mixedMessage.substr(0, found - 1);
    return {commandChannel, dataChannel};
}

typedef struct threadArg threadArg;

void* handleConnection(void* thread){
     threadArg *currArg = (threadArg *) thread;
     cerr << "argument commandFd " << currArg->commandChannel << "\n";
     cerr << "argument datafd" << currArg->dataChannel << "\n";
    MessageHandler* messageHandler = new MessageHandler(usersTosend, adminFilesToSend);
    // cout << messageHandler->usersFromServer.size() << "gg\n";
    char readClient[1024];
    string sendClient;
    while(true){
        memset(readClient, 0, 1024);
        bzero(readClient, 1024);
        bool dchanel;
        //cerr << "global commandFd " << arg.commandChannel << "\n";
        //cerr << "global dataFd " << arg.dataChannel << "\n";
        if(recv(currArg->commandChannel, readClient, sizeof(readClient), 0) > 0){
            cout << string(readClient) << " receive check\n";
            sendClient = messageHandler->handle(string(readClient));
            // cout << "Res: " << sendClient;
            dchanel = needDataChannel(sendClient);
        }
        else{
            error("ERROR: could not receive from client\n");
        }
        if(!dchanel){   // no need for data channel
            send(currArg->commandChannel, sendClient.c_str(), sizeof(readClient), 0);
        }
        else{
            vector<string> commandAndDataChannel = splitCommandData(sendClient);
            // cout << "command:" << commandAndDataChannel[0] << "\n";
            // cout << "data:" << commandAndDataChannel[1] << "\n";
            string commandSend = commandAndDataChannel[0];
            string dataSend = commandAndDataChannel[1];
            send(currArg->commandChannel, commandSend.c_str(), sizeof(readClient), 0);
            send(currArg->dataChannel, dataSend.c_str(), sizeof(readClient), 0);
        }
    }

}

void Server::run(){

    int commandChannel = setupServer(commandPort);
    int dataChannel = setupServer(dataPort);
    pthread_t threads[MAX_CLIENTS];  
    threadArg clientArg[MAX_CLIENTS];
    int numOfThreads = 0;
    usersTosend = users;
    while (true){
        int commandFd = acceptClient(commandChannel);
        int dataFd = acceptClient(dataChannel);
        cout << "commandFd : " << commandFd << "\n";
        cout << "dataFd : " << dataFd << "\n";
        
        if(commandFd == -1 || dataFd == -1)
            error("ERROR: could not accept client\n");
        
        clientArg[numOfThreads].commandChannel = commandFd;
        clientArg[numOfThreads].dataChannel = dataFd;
        //arg.commandChannel = commandFd;
        //arg.dataChannel = dataFd;
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