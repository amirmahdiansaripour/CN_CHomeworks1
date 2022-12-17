#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>

const int commandPort   = 8081;
const int dataPort      = 8084;

class Client{
public:
    Client();
    void run();
private:
    int connectServer(int port);
};

#endif