#include "User.h"
#include <assert.h>

User::User(int id, string userName, string password)
{
	this->id = id;
	this->userName = userName;
	this->password = password;

	//then store the whole user in the files from server class 
}


User::User(int id, string userName, string password, stack<Message> sentMessages,
	stack<Message> receivedMessages, deque<Message> favoriteMessages, vector<int> contacts)
{
	this->id = id;
	this->userName = userName;
	this->password = password;
	this->sentMessages = sentMessages;
	this->receivedMessages = receivedMessages;
	this->favoriteMessages = favoriteMessages;
	this->contacts = contacts;

}






void User::sendMessage(Message newMessage)
{
	//waiting ayman to explain  
	sentMessages.push(newMessage);
}

void User::recieveMessage(Message message)
{
	// waiting for bassel to add the function for storing massages 
	receivedMessages.push(message);
}

//to add massages to favorites 
void User::addToFavorite(Message message)
{
	// retrive data then ..
	favoriteMessages.push_front(message);
	//or we could add it to file directly ..
}

//to add contact 
void User::addContact(int contactId)
{
	//retrive data then .. 
	this->contacts.push_back(contactId);
	//or we could add it to file directly ..
}

void User::showContacts()
{
	//retriving data first 
	if (!contacts.empty()) {
		for (int contact = 0; contact < contacts.size(); contact++)
		{
			cout << contacts[contact] << endl;
		}
	}
}

void User::deleteLastFavorite()
{
	//retriving data first 
	if (!favoriteMessages.empty()) {
		favoriteMessages.pop_back();
	}
}

void User::undoLastMassage()
{
	/* we could use temporary variable approach or
	we could retrive data and do the following operation*/
	if (!sentMessages.empty()) {
		sentMessages.pop();
	}
}
// search for contact in my contacts
int User::searchContact(int id)
{
	return contacts[id];
}

void User::showSentMassages()
{
	//retriving data from dataset 
	assert(!sentMessages.empty());
	while (!sentMessages.empty())
	{
		cout << sentMessages.top().getMessageBody() << endl;
		sentMessages.pop();
	}
}

void User::showrecievedMassages()
{
	//retriving data from dataset 
	assert(!receivedMessages.empty());
	while (!receivedMessages.empty())
	{
		cout << receivedMessages.top().getMessageBody() << endl;
		receivedMessages.pop();
	}
}

int User::getID()
{
	return this->id;
}

string User::getUsername()
{
	return this->userName;
}

string User::getPassword()
{
	return this->password;
}

Message User::getLastMessage()
{
	if (!sentMessages.empty())
		return sentMessages.top();
	
}

