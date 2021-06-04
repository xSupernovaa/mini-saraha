#pragma once
#include <vector>
#include <string>
#include <map>
#include "User.h"

using namespace std;

class Server
{

private:

	static  vector<User> users;
	static int userCount;
	User* current_logged_user;
	map<string, pair<string, int>> users_credentials;

	//Cache
	/*cached data are cleared on each new login
	 and only contain data created on that session only*/
	/* there was no need for recieved messages cache since
	activity is only made by the logged in user*/
	deque<Message> sent_Messages_Cache;
	deque<Message> favorite_Messages_Cache;
	vector<int> added_Contacts_Cache;
	
public:
	
	bool isMessageDeletion;
	Server(); 
	void addContact(int targetId);
	void sendMessage(Message message);
	void deleteLastMessage();
	void viewMessages(int userId);
	void addFavoriteMessage(Message message);
	void delete_Last_Favorite_Message();
	bool registerUser(string username, string password);
	bool login(string username, string password);
	void saveSession();
	void loadSession();
	bool validate_password_registration(string password);
	bool validate_username_register(string username);
	User* get_Current_Logged_User();
	
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

