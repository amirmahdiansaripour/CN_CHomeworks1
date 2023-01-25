#include "../header/client.hpp"

using namespace std;

int main(int argc, char* argv[]){
    string serverPort = string(argv[1]).substr(10, string(argv[1]).size());
    string name = string(argv[2]);
    // cout << "serverPort:" << serverPort << "\n";
    // cout << "name:" << name << "\n";
    Client client = Client(stoi(serverPort), name);
    client.run();
}