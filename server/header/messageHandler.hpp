#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "../header/user.hpp"
#include <string>
#include <vector>

#define USER_SIGNIN "user"
#define PASS_SIGNIN "pass"

class MessageHandler{
public:
    MessageHandler(std::vector<User*>);
    std::string handle(std::string);

    int id;
    int loginUsername(std::string);
    int loginPassword(std::string);
    std::vector<User*> usersFromServer;
    User* incompleteLoginUser;
    bool loggedIn;
    bool incompleteLogin;
    User* currentUser;
    
};

#endif