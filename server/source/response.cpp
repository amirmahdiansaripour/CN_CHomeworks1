#include "../header/reponse.hpp"


std::string Response::getResponseMessage(int responseCode) 
{
	if (responseCode == USERNAME_FOUND) {
		return USERNAME_FOUND + ": User name okay, need password";
	}
}
