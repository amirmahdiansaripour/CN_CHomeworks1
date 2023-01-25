#ifndef _SERVER_H_
#define _SERVER_H_

#include <string>
#include <vector>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define MAX_CLIENTS 10

const int PORT = 8080;

class Server{
public:
    Server();
    void run();
    int setupServer(int);
    int acceptClient(int);
private:
    int port;

};




#endif