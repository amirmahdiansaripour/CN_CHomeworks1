#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
const string USER_SIGNIN = "user";

class MessageHandler{
public:
    MessageHandler(int id_);
    std::string handle(std::string message);
private:
    int id;
    int handleUsername(string username)
};

#endif