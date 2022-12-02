#include "../header/server.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Server server = Server(argv[1]);
    server.run();
}