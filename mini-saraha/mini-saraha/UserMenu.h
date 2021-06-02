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
	 void viewRecivedMessages(); 
	 void addToFavorite(int index);
	 void viewSentMessages();
	 void viewFavouriteMessages();
	 void usersSearch();
	 void displayUserData(User user);
	 void viewContacts(); 
	 void sendMessage(User user);
	 void selectContact();
	

};

