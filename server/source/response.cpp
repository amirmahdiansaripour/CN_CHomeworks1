#include "../header/response.hpp"

using namespace std;

Response::Response(){}

string Response::getResponseMessage(int responseCode) 
{
	string sendToClient;
	switch(responseCode)
	{
		case(USERNAME_FOUND):
			sendToClient = (to_string(responseCode) + ": User name okay, need password");
			break;

		case(INVALID_USER_PASS):
			sendToClient =  (to_string(responseCode) + ": Invalid username or password");
			break;

		case(PASS_WITHOUT_USER):
			sendToClient = (to_string(responseCode) + ": Bad sequence of commands");
			break;

		case(SUCCESSFUL_LOGIN):
			sendToClient = (to_string(responseCode) + ": User logged in, proceed. Logged out if appropriate.");
			break;

		case(HELP_CODE):
			sendToClient = (to_string(responseCode) + "\n" + helpResponse);
			break;
		
		case(QUIT_CODE):
			sendToClient = (to_string(responseCode) + ": Successful Quit.");
			break;

		default:
			sendToClient = "Error";
	}
	return sendToClient;
}
