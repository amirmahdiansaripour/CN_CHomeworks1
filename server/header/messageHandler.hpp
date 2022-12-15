#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "../header/user.hpp"
#include <string>
#include <vector>

#define USER_SIGNIN     "user"
#define PASS_SIGNIN     "pass"
#define HELP            "help"
#define QUIT            "quit"
class MessageHandler{
public:
    MessageHandler(std::vector<User*>);
    std::string handle(std::string);
    int loginUsername(std::string);
    int loginPassword(std::string);
    int clientQuit();
private:
    int id;
    std::vector<User*> usersFromServer;
    User* incompleteUser;
    User* currentUser;
    bool userEntered;
    bool passEntered;    
};

#endif