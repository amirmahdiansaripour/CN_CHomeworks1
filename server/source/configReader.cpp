#include "../header/configReader.hpp"

using namespace std;

ConfigReader::ConfigReader(const string path_){
    path = path_;
    readConfigFile();
}

ConfigReader::ConfigReader(){
}

void ConfigReader::readConfigFile(){
    // will be done soon!
}

vector<User> ConfigReader::getUsers(){
    return users;
}

vector<string> ConfigReader::getFilesNames(){
    return fileNames;
}