#include "../header/client.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Client client = Client(stoi(argv[1]));
    client.run();
}