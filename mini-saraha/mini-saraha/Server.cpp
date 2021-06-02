#include "Server.h"
#include <string>
#include <regex>
#include"FilesManager.h"
using namespace std;

vector<User> Server::users;
int Server::userCount;
FilesManager files;


Server::Server()
{
	users_credentials = files.load_users_credintials_from_disc();
	current_logged_user = NULL;
	userCount = users_credentials.size();
}

/**Add the reciver user to sender user's contact list*/
void Server::addContact(int recieverId)
{
	if (Server::idExists(recieverId))
	{
		current_logged_user->addContact(recieverId);

		//cache
		added_Contacts_Cache.push_back(recieverId);
	}
}


void Server::sendMessage(Message message)
{
	if (Server::idExists(message.getSenderId()) && Server::idExists(message.getRecieverId()))
	{
		User reciever = *Server::findUser(message.getRecieverId());
		reciever.recieveMessage(message);
		//cache
		sent_Messages_Cache.push(message);
	}
	else
		cout << "Sender or Reciver Id not found please check the ids and try again\n";
}

void Server::deleteLastMessage()
{
	Message lastMessage = current_logged_user->getLastMessage();
	int receiverId = lastMessage.getRecieverId();
	User receiver = *Server::findUser(receiverId);

	receiver.undoLastMassage();
	current_logged_user->undoLastMassage();

	

	//cache
	if (!sent_Messages_Cache.empty())
		sent_Messages_Cache.pop();
}

void Server::viewMessages(int senderId)
{
	if (Server::idExists(senderId))
	{
		Server::users[senderId].showrecievedMassages();
	}
}

void Server::addFavoriteMessage(Message message)
{
	current_logged_user->addToFavorite(message);

	//cache
	favorite_Messages_Cache.push_back(message);
}

void Server::delete_Last_Favorite_Message(Message message)
{
	current_logged_user->deleteLastFavorite();

	//cache
	if (!favorite_Messages_Cache.empty())
		favorite_Messages_Cache.pop_back();
}

bool Server::registerUser(string username, string password)
{
	//To check if username is already exist or dosen't exist
	bool _username = false;
	//To check if password match with pattern or not
	bool _password = false;

	_username = validate_username_register(username);
	_password = validate_password_registration(password);
	//I do more than (else if) to print to the user the specific problem of registration 
	//Username is incorrect 
	if (_username == false && _password == true)
	{
		cout << "Username is already taken, enter a username with at least 5 characters" << endl;
		return false;
	}
	//password is incorrect
	else if (_username == true && _password == false)
	{
		cout << "Please enter a password with at least on upper case, one lower case, one digit, one special character, minimum eight in length";
		return false;
	}
	//username and password is incorrect
	else if (_username == false && _password == false)
	{
		cout << "Username and password incorrect" << endl;
		return false;
	}
	else if (_username == true && _password == true)
	{	
		User new_user(userCount++, username, password);
		files.add_new_user_instance_to_disc(new_user);
		users_credentials = files.load_users_credintials_from_disc();
		return true;
	}
	
	
	
}

bool Server::validate_password_registration(string password)
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
bool Server::validate_username_register(string username)
{
	regex pattern("^(?=.*?[a-z]|[A-Z]).{5,}$");
	bool username_exist = users_credentials.count(username);
	bool password_match = regex_match(username, pattern);
	if (username_exist==true||password_match==false)
	{
		//username already exist or not match with pattern
		// Hazem : Show the user that he must enter a username consisting of letters and no less than five characters
		return false;
	}
	else
	{
		//username dosen't exist
		return true;
	}
}
bool Server::login(string username, string password)
{
	if (users_credentials.count(username) && users_credentials[username].first == password)
	{
		current_logged_user = findUser(users_credentials[username].second);
		return true;
	}
	else
	{
		return false;
	}
	
}

void Server::saveSession()
{

}
void Server::loadSession()
{
	for (int i = 0; i < userCount; i++) {
       users.push_back(files.load_user_instance_from_disc(i));
	}
	
}




User* Server::get_Current_Logged_User()
{
	return current_logged_user;
}

Server::~Server()
{

}


