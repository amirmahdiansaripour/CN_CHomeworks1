#ifndef _MESSAGE_HANDLER_
#define _MESSAGE_HANDLER_

#include "user.hpp"
#include <vector>
#include <sstream>
#include <iostream>

const std::vector<std::string> messageID = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", 
"1110", "1111"};

const std::string CONNECT   = "0001";      //1
const std::string CONNACK   = "0010";      //2
const std::string LIST      = "0011";      //3
const std::string LISTREPLY = "0100";      //4
const std::string INFO      = "0101";      //5
const std::string INFOREPLY = "0110";      //6
const std::string SEND      = "0111";      //7
const std::string SENDREPLY = "1000";      //8  
const std::string RECEIVE   = "1001";      //9
const std::string RECEIVEREPLY = "1010";   //10

const std::string QUITCOMMAND  = "quit";

class MessageHandler{
public:

    MessageHandler();
    std::string handle(std::string, int);
    std::string handleConnectReq(std::string, int);
    std::string handleListReq();
    std::string handleInfo(std::string);
    std::string handleSend(std::vector<std::string>);
    std::string handleQuit();
    User* findSender();
    std::string handleReceive();
private:
    std::vector<User*> users;
    int clientFd;
};



#endif