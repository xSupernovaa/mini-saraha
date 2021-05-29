#include "Server.h"
#include <string>
#include <regex>
#include"FilesManager.h"
using namespace std;

vector<User> Server::users;
int Server::userCount;
FilesManager files;

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

void registerUser(string username, string password)
{
	//To check if username is already exist or dosen't exist
	bool _username = false;
	//To check if password match with pattern or not
	bool _password = fasle;

	_username = validate_username_register(username);
	_password = validate_password_register(password);
	//I do more than (else if) to print to the user the specific problem of registration 
	//Username is incorrect 
	if (_username == false || _password == true)
	{
		cout << "Username is already taken" << endl;
	}
	//password is incorrect
	else if (_username == true || _password == false)
	{
		cout<<"Please enter a password with at least on upper case, one lower case, one digit, one special character, minimum eight in length"
	}
	//username and password is incorrect
	else if (_username == false && _password == false)
	{
		cout << "Username and password incorrect" << endl;
	}
	if (username == true && password == true)
	{	
		User new_user(userCounter++, username, name, password);
		files.add_new_user_instance_to_disc(new_user);
		login(username, password);
	}
	
	
	
}

bool validate_password_registration(string password)
{
	//This regex will enforce at least on upper case, one lower case, one digit, one special character, minimum eight in length
	regex pattern("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$");
	if (regex_match(password, pattern))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool validate_username_register(string username)
{
	map<string, pair<string, int>> users = files.load_users_credintials_from_disc();
	if (m1.count(username))
	{
		//username already exist
		return false;
	}
	else
	{
		//username dosen't exist
		return true;
	}
}

void login(string username, string password)
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


