#include "Server.h"
#include <string>

using namespace std;

vector<User> Server::users;
int Server::userCount;

/**Add the reciver user to sender user's contact list*/
void Server::addContact(int senderId, int recieverId)
{
	User sender = *Server::findUser(senderId);
	if (Server::idExists(recieverId))
	{
		//sender.addContact(recieverId);
	}
}


void Server::sendMessage(Message newMessage)
{
	if (Server::idExists(newMessage.getSenderId()) && Server::idExists(newMessage.getRecieverId()))
	{
		User reciever = *Server::findUser(newMessage.getRecieverId());
		reciever.recieveMessage(newMessage);
	}
	else
		cout << "Sender or Reciver Id not found please check the ids and try again\n";
}
void Server::deleteLastMessage()
{

}

void Server::viewMessages(int senderId)
{
	if (Server::idExists(senderId))
	{
		Server::users[senderId].showrecievedMassages();
	}
}

void Server::registerUser()
{

}


void Server::login()
{

}
void Server::saveSession()
{

}
void Server::loadSession()
{

}

Server::~Server()
{

}

