#pragma once
#include <vector>
#include <string>

//#include "User.h"
class Server
{
	//vector<User> 
	static int noUsers;


	//Cache
	
	//User current_logged_user;
	
public:
	Server();
	void addUser(int sourceId, int targetId);
	void sendMessage(int sourceId, int targetId, string message);
	void deleteLastMessage();
	void viewMessages(int userId);
	void registerUser();
	void login();
	void saveSession();
	void loadSession();
	~Server();


	static int findUser(int id)
	{

	}

};

