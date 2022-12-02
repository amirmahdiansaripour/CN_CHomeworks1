#include "../header/server.hpp"

using namespace std;

Server::Server(const string path){

    configReader = ConfigReader(path);
    fileNames = configReader.getFilesNames();
    users = configReader.getUsers();

}

void Server::run(){
    
}