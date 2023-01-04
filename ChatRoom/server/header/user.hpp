#ifndef _USER_H_
#define _USER_H_

#include <string>

class User{
public:
    User(std::string, int);
    int getID();
    std::string getName();
private:

    std::string name;
    int id;

};


#endif