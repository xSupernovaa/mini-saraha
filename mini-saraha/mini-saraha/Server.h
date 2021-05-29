#pragma once
#include <vector>
#include <string>
#include "User.h"

using namespace std;

class Server
{

	//Cache
	
	User* current_logged_user;
	
public:
	static  vector<User> users;
	static int userCount;

	Server(); 
	void addContact(int sourceId, int targetId);
	void sendMessage(Message message);
	void deleteLastMessage();
	void viewMessages(int userId);
	void registerUser();
	void login();
	void saveSession();
	void loadSession();
	~Server();


	static User* findUser(int id)
	{
		if (id >= 0 && id <= userCount)
			return &users[id];
		else
			cout << "User Id out of bounds\n";

		return nullptr;
	}

	 static bool idExists(int userID)
	{
		return (userID >= 0 && userID <= userCount);
	}

};

