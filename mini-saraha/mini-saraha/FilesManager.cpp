#include "FilesManager.h"

map<string, pair<string, int>> FilesManager:: load_users_credintials_from_disc()
{
	map<string, pair<string, int>> user_credintials;

	filesReader.open("data/user_credintials.txt");

	if (filesReader.is_open())
	{
		string username;
		string password;
		int id;

		while (filesReader >> username >> password >> id)
		{
			user_credintials[username].first = password;
			user_credintials[username].second = id;
		}
	}
	else
	{
		cout << "Fatal error, couldn't load user credintials, terminating...\n";
		exit(-1);
	}

	filesReader.clear();
	filesReader.close();

	return user_credintials;
}


void FilesManager::add_new_user_instance_to_disc(User new_user)
{	
	string folder_name = "user_" + to_string(new_user.getID());
	string folder_path = make_new_user_folder(folder_name);
	create_new_user_data_files(folder_path);
	add_new_user_credintials_to_disc(new_user.getUsername(), new_user.getPassword(), new_user.getID());
}
 

string FilesManager::make_new_user_folder(string folder_name)
{
	string folder_path_string = "data/users/" + folder_name;
	const char* folder_path = folder_path_string.c_str();

	if (_mkdir(folder_path) != 0)
	{	
		cout << "Error, User folder already exists, terminating...\n";
		exit(-1);
	}
	
	return folder_path;
}


// IMPORTANT: it is assumed that the username is not already in the database, delete this comment when it's done 
void FilesManager::add_new_user_credintials_to_disc(string username, string password, int id)
{
	filesWriter.open("data/user_credintials.txt", ofstream::app);

	if (filesWriter.is_open())
	{
		filesWriter << username << ' ' << password << ' ' << id << '\n';
	}
	else
	{
		cout << "Erorr, couldn't add new user to database\n";
	}

	filesWriter.clear();
	filesWriter.close();
}


void FilesManager::create_new_user_data_files(string folder_path)
{
	string sent_messages_string = folder_path + "/sent_messages.txt";
	string received_messages_string = folder_path + "/received_messages.txt";
	string contacts_string = folder_path + "/contacts.txt";
	string favorite_messages_string = folder_path + "/favorite_messages.txt";

	const char* sent_messages = sent_messages_string.c_str();
	const char* received_messages = received_messages_string.c_str();
	const char* contacts = contacts_string.c_str();
	const char* favorite_messages = favorite_messages_string.c_str();

	// create sent_messages.txt
	filesWriter.open(sent_messages);
	filesWriter.clear();
	filesWriter.close();

	// create received_messages.txt
	filesWriter.open(received_messages);
	filesWriter.clear();
	filesWriter.close();

	// create contacts.txt
	filesWriter.open(contacts);
	filesWriter.clear();
	filesWriter.close();

	// create favorite_messages.txt
	filesWriter.open(favorite_messages);
	filesWriter.clear();
	filesWriter.close();
}