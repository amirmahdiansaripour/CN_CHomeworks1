#ifndef _MESSAGE_HANDLER_
#define _MESSAGE_HANDLER_

#include "user.hpp"
#include <vector>
#include <iostream>

const std::vector<std::string> messageID = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", 
"1110", "1111"};

const std::string CONNECT   = "0001";      //1
const std::string CONNACK   = "0010";      //2
const std::string LIST      = "0011";      //3
const std::string LISTREPLY = "0100";      //4
const std::string INFO      = "0101";      //5

class MessageHandler{
public:

    MessageHandler();
    std::string handle(std::string);
    std::string handleConnectReq(std::string);
    std::string handleListReq();
    std::string handleInfo(std::string);
    std::vector<User*> getUsers();
private:
    std::vector<User*> users;
};



#endif