#include "../header/reponse.hpp"


std::string Response::getResponseMessage(int responseCode) 
{
	switch(responseCode)
	{
		case(USERNAME_FOUND):
			return responseCode + ": User name okay, need password";

		case(INVALID_USER_PASS):
			return responseCode + ": Invalid username or password";

		case(PASS_WITHOUT_USER):
			return responseCode + ": Bad sequence of commands";
		
		case(SUCCESSFUL_LOGIN):
			return responseCode + ": User logged in, proceed. Logged out if appropriate.";
	}
}
