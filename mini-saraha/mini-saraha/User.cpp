#include "User.h"

User::User(int id, string userName,string name, string password)
{
	this->id = id;
	this->name = name;
	this->userName = userName;
	this->password = password;

	//then store the whole user in the files from server class 
}

void User::sendMassage(int senderId, int recieverId, string meassage)
{
	//sending massage to another user in the server 
}

//to add massages to favorites 
void User::addToFavorite(int massageId)
{
	// retrive data then ..
	favoriteMassages.push_front(massageId);
	//or we could add it to file directly ..
}

//to add contact 
void User::addContact(User contactId)
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
			cout << contacts[contact].name << " " << contacts[contact].id << endl;
		}
	}
}

void User::deleteLastFavorite()
{
	//retriving data first 
	if (!favoriteMassages.empty()) {
		favoriteMassages.pop_back();
	}
}

void User::undoLastMassage()
{
	/* we could use temporary variable approach or 
	we could retrive data and do the following operation*/
	if (!sentMassages.empty()) {
		sentMassages.pop();
	}
}

void User::searchUser()
{
	//searching for user in server 
}

void User::showSentMassages()
{
	//retriving data from dataset 
}

void User::showrecievedMassages()
{
	//retriving data from dataset 
}
