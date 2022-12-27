#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>

const int commandPort   = 8080;
const int dataPort      = 8081;

class Client{
public:
    Client();
    void run();
private:
    int connectServer(int port);
};

#endif