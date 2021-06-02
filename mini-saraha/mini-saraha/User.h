#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<deque>
#include<queue>
#include "Message.h"

using namespace std;
class User
{
private:
	int id;
	string userName;
	string password;
	vector<int> contacts;
	queue<Message> sentMessages;
	deque<Message> receivedMessages;
	deque<Message> favoriteMessages;
public:
	User(int id, string userName, string password);
	User(int id, string userName, string password, queue<Message> sentMessages,
		deque<Message> receivedMessages, deque<Message> favoriteMessages, vector<int> contacts);
	void sendMessage(Message message);
	void recieveMessage(Message message);
	void addToFavorite(Message message);
	void addContact(int contactId);
	void showContacts();
	void deleteLastFavorite();
	void undoLastMassage();
	int  searchContact(int id);
	void showSentMassages();
	void showrecievedMassages();
	void showfavoriteMassages();
	int getID();
	bool foundMessages();
	bool foundSentMessages();
	bool foundFavouriteMessages();
	bool foundContacts(); 
	string getUsername();
	string getPassword();
	Message getLastMessage();
	Message getReceivedMessages(int index);
	vector<int> getContacts();
	queue<Message> getSentMessages();
	deque<Message> getRecievedMessages();
	deque<Message> getFavoriteMessages();


};

