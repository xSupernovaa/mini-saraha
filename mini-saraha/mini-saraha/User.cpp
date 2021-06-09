#include "User.h"

User::User(int id, string userName, string password)
{
	this->id = id;
	this->userName = userName;
	this->password = password;
 
}


User::User(int id, string userName, string password, deque<Message> sentMessages,
	deque<Message> receivedMessages, deque<Message> favoriteMessages, vector<int> contacts)
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
	sentMessages.push_back(newMessage);
}

void User::recieveMessage(Message message)
{
	// waiting for bassel to add the function for storing massages 
	receivedMessages.push_back(message);
}

//to add massages to favorites 
void User::addToFavorite(Message message)
{

	favoriteMessages.push_back(message);

}

bool User::isfavoriteFound(Message message)
{
	for (int i = 0; i < favoriteMessages.size(); i++) {
		if (!message.getMessageBody().compare(favoriteMessages[i].getMessageBody()) && message.getSenderId() == favoriteMessages[i].getSenderId()
			&& message.getRecieverId() == favoriteMessages[i].getRecieverId())
			return true;
	}
	return false;
}

bool User::isContactFound(int contactId) {
	for (int i = 0; i < contacts.size(); i++) {
		if (contacts[i] == contactId) return true;
	}
	return false;
}

//to add contact 
void User::addContact(int contactId)
{
	contacts.push_back(contactId);
	
}


void User::deleteLastFavorite()
{
	//retriving data first 
	if (!favoriteMessages.empty()) {
		favoriteMessages.pop_front();
	}
}

void User::undoLastSentMassage()
{
	if (!sentMessages.empty()) {
		sentMessages.pop_back();
	}
}

/* iterate over received messages, the first match of sender
	is the message to be deleted*/
void User::undoLastRecievedMessage(int senderId)
{	
	for (int i = 0; i < receivedMessages.size(); i++)
	{
		if (receivedMessages[i].getSenderId() == senderId)
			receivedMessages.erase(receivedMessages.begin() + i);
	}
}

// search for contact in my contacts
int User::searchContact(int id)
{
	return contacts[id];
}



vector<Message> User::showAllSenders(int sender)
{
	
	deque<Message> showedMessages = receivedMessages;
	vector<Message> temp;
	int i = 1;
    showedMessages = receivedMessages;
	while (!showedMessages.empty())
	{
		if (sender == showedMessages.back().getSenderId()) {
			temp.push_back(showedMessages.back());
		}
		showedMessages.pop_back();
	}

	return temp;
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
		return sentMessages.back();
}

Message User::getReceivedMessage(int index)
{
	if (index >= 0 and index <= receivedMessages.size())
		return receivedMessages[index-1];
	else
		cout << "ERROR! Message index out of bounds\n";
}

bool User::foundMessages()
{
	return receivedMessages.size();
}

bool User::foundSentMessages()
{
	return sentMessages.size();
}

bool User::foundFavouriteMessages()
{
	return favoriteMessages.size();
}
bool User::foundContacts()
{
	return contacts.size();
}
vector<int> User::getContacts()
{
	return contacts;
}
deque<Message> User::getSentMessages()
{
	return sentMessages;
}

deque<Message> User::getRecievedMessages()
{
	
	return receivedMessages;
}
deque<Message> User::getFavoriteMessages()
{
	return favoriteMessages;
}