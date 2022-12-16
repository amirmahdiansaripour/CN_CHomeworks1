#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>

class Client{
public:
    Client();
    void run();
private:
    int connectServer(int port);
};

#endif