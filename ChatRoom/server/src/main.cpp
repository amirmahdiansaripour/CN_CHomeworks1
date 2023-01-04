#include "../header/server.hpp"

using namespace std;

int main(int argc, char* argv[]){
    // cout << stoi(argv[1]) << "\n";
    Server server = Server();
    server.run();
}