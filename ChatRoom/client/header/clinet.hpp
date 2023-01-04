#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>


class Client{
public:
    Client(int);
    void run();
    int connectServer(int);

private:
    int port;
};

#endif