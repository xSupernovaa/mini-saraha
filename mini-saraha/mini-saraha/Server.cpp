#include "Server.h"
#include <string>

using namespace std;

vector<User> Server::users;
int Server::userCount;

/**Add the reciver user to sender user's contact list*/
void addContact(int senderId, int recieverId)
{
	User sender = *Server::findUser(senderId);
	if (Server::idExists(recieverId))
	{
		//sender.addContact(recieverId);
	}
}


void sendMessage(int senderId, int recieverId, string message)
{
	if (Server::idExists(senderId) && Server::idExists(recieverId))
	{
		User reciever = *Server::findUser(recieverId);
		reciever.sendMassage(senderId, recieverId, message);
	}
	else
		cout << "Sender or Reciver Id not found please check the ids and try again\n";
}
void deleteLastMessage()
{

}

void viewMessages(int senderId)
{
	if (Server::idExists(senderId))
	{
		Server::users[senderId].showrecievedMassages();
	}
}

void registerUser()
{

}


void login()
{

}
void saveSession()
{

}
void loadSession()
{

}

Server::~Server()
{

}


