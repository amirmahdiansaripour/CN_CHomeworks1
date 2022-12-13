#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "../header/user.hpp"
#include <string>
const std::string USER_SIGNIN = "user";
const std::string PASS_SIGNIN = "pass";

class MessageHandler{
public:
    MessageHandler(int id_, std::vector<User> _users);
    std::string handle(std::string message);
private:
    int id;
    int loginUsername(std::string username);
    int loginPassword(std::string password);
    std::vector<User> users;
    User* incompleteLoginUser;
    bool loggedIn;
    bool incompleteLogin;
    User* currentUser;
    
};

#endif