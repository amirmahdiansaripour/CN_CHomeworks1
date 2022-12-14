#ifndef CLIENT_H
#define CLIENT_H

class Client{
public:
    Client();
    void run();
private:
    int connectServer(int port);
};

#endif