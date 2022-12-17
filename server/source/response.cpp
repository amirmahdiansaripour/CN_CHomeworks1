#include "../header/response.hpp"

using namespace std;

Response::Response(){}

string Response::getResponseMessage(int responseCode) 
{
	string sendToClient;
	string code = to_string(responseCode);
	switch(responseCode)
	{
		case(USERNAME_FOUND):
			sendToClient = (code + ": User name okay, need password");
			break;

		// case(INVALID_USER_PASS):
		// 	sendToClient =  (code + ": Invalid username or password");
		// 	break;

		// case(PASS_WITHOUT_USER):
		// 	sendToClient = (code + ": Bad sequence of commands");
		// 	break;

		case(SUCCESSFUL_LOGIN):
			sendToClient = (code + ": User logged in, proceed. Logged out if appropriate.");
			break;

		case(HELP_CODE):
			sendToClient = (code + "\n" + helpResponse);
			break;
		
		case(QUIT_CODE):
			sendToClient = (code + ": Successful Quit.");
			break;

		case(DOWNLOAD_CODE):	// TAs should change upload code
			sendToClient = (code + ": Successful Download.");
			break;

		// case(FILE_UNAVAILABLE):
		// 	sendToClient = (code + ": File unavailable.");
		// 	break;

		// case(CAPACITY_LACKAGE):
		// 	sendToClient = (code + ": Can't open data connection.");
		// 	break;
			
		default:
			sendToClient = "Error";
	}
	return sendToClient;
}
