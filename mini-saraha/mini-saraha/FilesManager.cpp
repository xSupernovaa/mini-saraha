#include "FilesManager.h"

map<string, string> FilesManager:: load_users_credintials_from_disc()
{
	map<string, string> user_credintials;

	filesReader.open("data/user_credintials.txt");

	if (filesReader.is_open())
	{
		string username;
		string password;

		while (filesReader >> username >> password)
		{
			user_credintials[username] = password;
		}
	}
	else
	{
		cout << "Fatal error, couldn't load user credintials\n";
	}

	filesReader.clear();
	filesReader.close();

	return user_credintials;
}



// IMPORTANT: it is assumed that the username is not already in the database, delete this comment when it's done 
void FilesManager::add_new_user_credintials_to_disc(string username, string password)
{
	filesWriter.open("data/user_credintials.txt", ofstream::app);

	if (filesWriter.is_open())
	{
		filesWriter << username << ' ' << password << '\n';
	}
	else
	{
		cout << "Erorr, couldn't add new user to database\n";
	}

	filesWriter.clear();
	filesWriter.close();
}