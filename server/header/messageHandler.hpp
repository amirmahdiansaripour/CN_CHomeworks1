#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>

class MessageHandler{
public:
    MessageHandler(int id_);
    std::string handle(std::string message);
private:
    int id;

};

#endif