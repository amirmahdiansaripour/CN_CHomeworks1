#include "../header/response.hpp"

using namespace std;

string Response::getResponseMessage(int responseCode) 
{
	string res = "Error";
	// cout << "code : " << responseCode << "\n";
	switch(responseCode)
	{
		case(USERNAME_FOUND):
			res = (to_string(responseCode) + ": User name okay, need password");

		case(INVALID_USER_PASS):
			res =  (to_string(responseCode) + ": Invalid username or password");

		case(PASS_WITHOUT_USER):
			res = (to_string(responseCode) + ": Bad sequence of commands");
		
		case(SUCCESSFUL_LOGIN):
			res = (to_string(responseCode) + ": User logged in, proceed. Logged out if appropriate.");
	}
	return res;
}
