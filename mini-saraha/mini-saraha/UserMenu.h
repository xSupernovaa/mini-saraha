#pragma once
#include "User.h"
#include "Server.h"
class UserMenu
{
	User* userP;
	Server* serverP;
public:
	UserMenu(Server server);
	 void initial(); 
	 void viewMessages();

};

