#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>

const int PORT = 8080;

class Client{
public:
    Client();
    void run();
    int connectServer(int);

private:
    int port;
};

#endif