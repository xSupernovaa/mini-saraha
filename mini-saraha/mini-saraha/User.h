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
	deque<Message> sentMessages; // deque to support both undo and chronological saving to files
	deque<Message> receivedMessages;
	deque<Message> favoriteMessages;
	
public:
	User(int id, string userName, string password);
	User(int id, string userName, string password, deque<Message> sentMessages,
		deque<Message> receivedMessages, deque<Message> favoriteMessages, vector<int> contacts);
	void sendMessage(Message message);
	void recieveMessage(Message message);
	void addToFavorite(Message message);
	bool isfavoriteFound(Message message);
	void addContact(int contactId);
	bool isContactFound(int contactId);
	void deleteLastFavorite();
	void undoLastSentMassage();
	void undoLastRecievedMessage(int senderId);
	int  searchContact(int id);
	vector<Message> showAllSenders(int sender);
	int getID();
	bool foundMessages();
	bool foundSentMessages();
	bool foundFavouriteMessages();
	bool foundContacts(); 
	string getUsername();
	string getPassword();
	Message getLastMessage();
	Message getReceivedMessage(int index);
	vector<int> getContacts();
	deque<Message> getSentMessages();
	deque<Message> getRecievedMessages();
	deque<Message> getFavoriteMessages();

};

