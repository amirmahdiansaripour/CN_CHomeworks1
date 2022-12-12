#ifndef RESPONSE_H
#define RESPONSE_H

const int USERNAME_FOUND = 331;
const int INVALID_USER_PASS = 230;

class Response {
public:
	string getResponseMessage(int responseCode);

};
#endif // !RESPONSE_H
