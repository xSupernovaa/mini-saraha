#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<deque>
#include<stack>

using namespace std;
class User
{
private:
	int id;
	string name;
	string userName;
	string password;
	vector<User> contacts;
	stack<string> sentMassages;
	stack<string> receivedMassages;
	deque<int> favoriteMassages;
public:
	User(int id, string userName, string name, string password);
	void sendMassage(int senderId, int recieverId, string meassage);
	void addToFavorite(int massageId);
	void addContact(User contactId);
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

