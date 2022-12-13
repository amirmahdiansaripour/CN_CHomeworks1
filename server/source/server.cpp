#include "../header/server.hpp"
#include "../header/messageHandler.hpp"

using namespace std;

Server::Server(const string path){

    configReader = ConfigReader(path);
    fileNames = configReader.getFilesNames();
    users = configReader.getUsers();

}

void Server::run(){

}

void* Server::handleConnection(void* command, void* command_id){
    MessageHandler* messageHandler = new MessageHandler(*(int* ) command_id, users);
    // connections and reqs from clients are handled here.
}