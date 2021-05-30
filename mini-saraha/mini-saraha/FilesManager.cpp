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
	string sent_messages = folder_path + "/sent_messages.txt";
	string received_messages = folder_path + "/received_messages.txt";
	string contacts = folder_path + "/contacts.txt";
	string favorite_messages = folder_path + "/favorite_messages.txt";

	create_new_user_file(sent_messages);
	create_new_user_file(received_messages);
	create_new_user_file(contacts);
	create_new_user_file(favorite_messages);
}

void FilesManager::create_new_user_file(string file_path)
{
	const char* file_name = file_path.c_str();
	filesWriter.open(file_name);
	filesWriter.clear();
	filesWriter.close();
}
