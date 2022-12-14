#include "../header/configReader.hpp"

using namespace std;

ConfigReader::ConfigReader(const string path_){
    path = path_;
    readConfigFile();
}

ConfigReader::ConfigReader(){
}

// void ConfigReader::addUser(auto record){
//     string username = record["user"].get<string>();
//     string password = record["password"].get<string>();
//     bool isAdmin = false;
//     string admin = record["admin"].get<string>(); 
//     if(admin == "true")
//         isAdmin = true;
//     int size = stoi(record["size"].get<string>());
//     User newUser = User(username, password, size, isAdmin);
//     newUser.printUserData();
//     users.push_back(newUser);
// }

void ConfigReader::printData(){
    for(User user : users){
        user.printUserData();
    }
    for(string fileName : fileNames){
        cout << fileName << "\n";
    }
}

void ConfigReader::readConfigFile(){
    ifstream inputFile(path);
    json j;
    inputFile >> j;
    for(auto record: j["users"]){
        string username = record["user"].get<string>();
        string password = record["password"].get<string>();
        bool isAdmin = false;
        string admin = record["admin"].get<string>(); 
        if(admin == "true")
            isAdmin = true;
        int size = stoi(record["size"].get<string>());
        User newUser = User(username, password, size, isAdmin);
        users.push_back(newUser);
    }

    for(auto fileRecord: j["files"])
        fileNames.push_back(fileRecord.get<string>());

    // printData();

}

vector<User> ConfigReader::getUsers(){
    return users;
}

vector<string> ConfigReader::getFilesNames(){
    return fileNames;
}