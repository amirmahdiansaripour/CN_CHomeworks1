#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include <iostream>
const int USERNAME_FOUND = 331;
const int INVALID_USER_PASS = 430;
const int PASS_WITHOUT_USER = 503;
const int SUCCESSFUL_LOGIN = 230;
const int FILE_UNAVAILABLE = 550;
const int DEFAULT_ERROR = 500;


class Response {
public:
	Response();
	std::string getResponseMessage(int responseCode);

};
#endif // !RESPONSE_H
