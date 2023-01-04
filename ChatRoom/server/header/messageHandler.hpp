#ifndef _MESSAGE_HANDLER_
#define _MESSAGE_HANDLER_

#include "user.hpp"
#include <vector>


class MessageHandler{
public:

    MessageHandler(std::vector<User*>);
    std::string handle(std::string);

private:
    std::vector<User*> users;

};



#endif