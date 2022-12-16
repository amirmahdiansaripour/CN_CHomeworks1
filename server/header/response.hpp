#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include <iostream>

const int USERNAME_FOUND 	= 331;
const int INVALID_USER_PASS = 430;
const int PASS_WITHOUT_USER = 503;
const int SUCCESSFUL_LOGIN 	= 230;
const int FILE_UNAVAILABLE 	= 550;
const int DEFAULT_ERROR 	= 500;
const int HELP_CODE 		= 214;
const int QUIT_CODE 		= 221;
const int DOWNLOAD_CODE		= 226;
const int UPLOAD_CODE		= 226;

const std::string userHelp = "USER [name], Its argument is used to specify the user's string. It is used for user authentication.\n";
const std::string passHelp = "PASS [password], Its argument is used to specify the user's string. It is used for user authorization.\n";
const std::string downloadHelp = "RETR [name], Its argument is used to specify the user's string. It is used for downloading an existing file.\n";
const std::string uploadHelp = "UPLOAD [name], Its argument is used to specify the user's string. It is used for uploading an existing file.\n";
const std::string quitHelp = "QUIT, It is used for quitting from the system.\n";

const std::string helpResponse = userHelp + passHelp + downloadHelp + uploadHelp + quitHelp;

class Response {
public:
	Response();
	std::string getResponseMessage(int responseCode);

};
#endif // !RESPONSE_H
