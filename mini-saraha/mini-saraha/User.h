#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<deque>
#include<stack>
#include "Message.h"
#include "Server.h"

using namespace std;
class User
{
private:
	int id;
	string userName;
	string password;
	vector<int> contacts;
	stack<Message> sentMessages;
	stack<Message> receivedMessages;
	deque<Message> favoriteMessages;
public:
	User(int id, string userName, string password);
	void sendMessage(Message message);
	void recieveMessage(Message message);
	void addToFavorite(Message message);
	void addContact(int contactId);
	void showContacts();
	void deleteLastFavorite();
	void undoLastMassage();
	void searchUser();
	void showSentMassages();
	void showrecievedMassages();
	int getID();
	string getUsername();
	string getPassword();
};

