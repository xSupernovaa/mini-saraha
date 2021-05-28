#include "Server.h"

Server::Server()
{

}

/**Add the targer user to source user's contact list*/
void addContact(int senderId, int recieverId)
{
	User sender = Server::findUser(senderId);
	if (Server::idExists(recieverId))
		sender.addContact(Server::findUser(recieverId));
}


void sendMessage(int senderId, int recieverId, string message)
{

}
void deleteLastMessage()
{
	
}

void viewMessages(int userId)
{

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


