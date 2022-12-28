#include "HttpServer.hpp"

#include <vector>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
vector<string> parseInput(char* argv)
{
    stringstream ss;
    ss << string(argv);
    vector<string> parsed;

    std::string item;
    while(getline(ss, item, ':'))
    {
        parsed.push_back(item);
    }
    return parsed;

}
int main(int argc, char* argv[])
{
    std::vector<std::string> parsedArgs = parseInput(argv[1]);
    HttpServer server(parsedArgs[0], stoi(parsedArgs[1]));
    server.run();
    return 0;
}