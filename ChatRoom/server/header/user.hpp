#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <vector>

class User{
public:
    User(std::string, int, int);
    int getID();
    int getChannel();
    void addToArchive(std::string);
    std::string getName();
private:

    std::string name;
    int id;
    int channel;
    std::vector<std::string> archiveMessages;

};


#endif