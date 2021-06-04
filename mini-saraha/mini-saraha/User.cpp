#include "User.h"

User::User(int id, string userName, string password)
{
	this->id = id;
	this->userName = userName;
	this->password = password;
 
}


User::User(int id, string userName, string password, queue<Message> sentMessages,
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
	sentMessages.push(newMessage);
}

void User::recieveMessage(Message message)
{
	// waiting for bassel to add the function for storing massages 
	receivedMessages.push_back(message);
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
	contacts.push_back(contactId);
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

void User::undoLastSentMassage()
{
	/* we could use temporary variable approach or
	we could retrive data and do the following operation*/
	if (!sentMessages.empty()) {
		sentMessages.pop();
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

void User::showSentMassages()
{
	if (sentMessages.empty()) {
		cout << "You don't have any messages\n";
		return;
	}
	//retriving data from dataset 
	queue<Message> showedMessages = sentMessages;
	while (!showedMessages.empty())
	{
		cout << showedMessages.front().getMessageBody() << endl;
		showedMessages.pop();
	}
}

void User::showrecievedMassages()
{
	if (receivedMessages.empty()) {
		cout << "You don't have any messages\n";
		return;
	}
	deque<Message> showedMessages = receivedMessages;
	//retriving data from dataset 
	while (!showedMessages.empty())
	{
		cout << showedMessages.front().getMessageBody() << endl;
		showedMessages.pop_back();
	}
}

void User::showfavoriteMassages()
{
	if (favoriteMessages.empty()) {
		cout << "You don't have any messages\n";
		return;
	}
	//retriving data from dataset 
	deque<Message> showedMessages = favoriteMessages;
	while (!showedMessages.empty())
	{
		cout << showedMessages.back().getMessageBody() << endl;
		showedMessages.pop_back();
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
		return sentMessages.front();
}

Message User::getReceivedMessages(int index)
{
	return receivedMessages[index];
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
queue<Message> User::getSentMessages()
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