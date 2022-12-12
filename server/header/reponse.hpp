#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
const int USERNAME_FOUND = 331;
const int INVALID_USER_PASS = 230;

class Response {
public:
	std::string getResponseMessage(int responseCode);

};
#endif // !RESPONSE_H
