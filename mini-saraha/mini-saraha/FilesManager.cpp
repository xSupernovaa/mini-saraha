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
	add_user_basicData_to_disc(new_user.getUsername(), new_user.getPassword(), new_user.getID(), folder_path);
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
	string basic_data = folder_path + "/basic_data.txt";
	create_new_user_file(sent_messages);
	create_new_user_file(received_messages);
	create_new_user_file(contacts);
	create_new_user_file(favorite_messages);
	create_new_user_file(basic_data);
}




void FilesManager::create_new_user_file(string file_path)
{
	const char* file_name = file_path.c_str();
	filesWriter.open(file_name);
	filesWriter.clear();
	filesWriter.close();
}

void FilesManager::add_user_basicData_to_disc(string username, string password, int id, string folderPath)
{
	string filePath = folderPath + "/basic_data.txt";
	filesWriter.open(filePath, ofstream::app);
	if (filesWriter.is_open())
		filesWriter << username << " " << password << " " << id;
	else
	{
		cout << "Failed to write basic data to file, Terminating..\n";
		exit(-1);
	}
	filesWriter.clear();
	filesWriter.close();
}


User FilesManager::load_user_instance_from_disc(int user_id)
{
	string user_folder_path = "data/users/user_" + to_string(user_id);
	
	string sent_messages_file = user_folder_path + "/sent_messages.txt";
	string received_messages_file = user_folder_path + "/received_messages.txt";
	string contacts_file = user_folder_path + "/contacts.txt";
	string favorite_messages_file = user_folder_path + "/favorite_messages.txt";
	string basic_data_file = user_folder_path + "/basic_data.txt";


	deque <Message> sent_messages = load_user_messages_from_disc(sent_messages_file);
	deque <Message> received_messages = load_user_messages_from_disc(received_messages_file);
	deque <Message> favorite_messages = load_user_messages_from_disc(favorite_messages_file);
	vector<int> contacts = load_user_contants_from_disc(contacts_file);
	vector<string> basic_data = load_user_basic_data_from_disc(basic_data_file);


	User user(user_id, basic_data[0], basic_data[1], sent_messages, received_messages,
		favorite_messages, contacts);

	return user; // تم بحمد الله
}


deque<Message> FilesManager::load_user_messages_from_disc(string messages_file_path)
{

	const char* messages_file_path_const = messages_file_path.c_str();

	deque<Message> messages;

	filesReader.open(messages_file_path_const);

	if (filesReader.is_open())
	{
		int sender_id, receiver_id;
		string message_body;

		while (filesReader >> sender_id >> receiver_id >> message_body)
		{
			Message message(sender_id, receiver_id, message_body);
			messages.push_back(message);
		}
	}
	else
	{
		cout << "Fatal error, couldn't load user messages, terminating...\n";
		exit(-1);
	}

	filesReader.clear();
	filesReader.close();

	return messages;
}



vector<int> FilesManager::load_user_contants_from_disc(string contacts_file_path)
{
	const char* contacts_file_path_const = contacts_file_path.c_str();

	vector<int> contacts;

	filesReader.open(contacts_file_path_const);

	if (filesReader.is_open())
	{
		
		int contact_id;

		while (filesReader >> contact_id)
		{
			contacts.push_back(contact_id);
		}
	}
	else
	{
		cout << "Fatal error, couldn't load user contacts, terminating...\n";
		exit(-1);
	}

	filesReader.clear();
	filesReader.close();

	return contacts;

}


vector<string> FilesManager:: load_user_basic_data_from_disc(string basic_data_file_path)
{
	const char* basic_data_file_path_const = basic_data_file_path.c_str();

	vector<string> basic_data;

	filesReader.open(basic_data_file_path_const);

	if (filesReader.is_open())
	{
		string user_name, password;

		filesReader >> user_name;
		filesReader >> password;

		basic_data.push_back(user_name);
		basic_data.push_back(password);
	}
	else
	{
		cout << "Fatal error, couldn't load user basic data, terminating...\n";
		exit(-1);
	}

	filesReader.clear();
	filesReader.close();

	return basic_data;


}


void FilesManager::add_user_data_to_disk(int logged_user_id,
										 bool isMessageDeletion,
										 deque<Message> &sent_messages,
										 deque<Message> &favorite_messages,
										 vector<int> &added_contacts)
{
	string user_folder_path = "data/users/user_" + to_string(logged_user_id);
	//auto writeType = isMessageDeletion ? ofstream::trunc : ofstream::app;
	auto writeType = ofstream::app;

	string sent_messages_file = user_folder_path + "/sent_messages.txt";
	
	while (!sent_messages.empty())
	{

		// Add message to sender files
		filesWriter.open(sent_messages_file, writeType);
		if (filesWriter.is_open())
		{
			filesWriter << sent_messages.front().getSenderId() << " " <<
				sent_messages.front().getRecieverId() << " " <<
				sent_messages.front().getMessageBody() << endl;

		}
		else
		{
			cout << "Error While saving session, Terminating..\n";
			exit(-1);
		}
		filesWriter.clear();
		filesWriter.close();

		//Add message to reciever files
		string receiver_folder_path = "data/users/user_" + to_string(sent_messages.front().getRecieverId());
		string received_messages_file = receiver_folder_path + "/received_messages.txt";

		filesWriter.open(received_messages_file, writeType);
		if (filesWriter.is_open())
		{
			filesWriter << sent_messages.front().getSenderId() << " " <<
				sent_messages.front().getRecieverId() << " " <<
				sent_messages.front().getMessageBody() << endl;
		}
		else
		{
			cout << "Error While saving session, Terminating..\n";
			exit(-1);
		}
		filesWriter.clear();
		filesWriter.close();

		sent_messages.pop_front();
	}


	string contacts_file = user_folder_path + "/contacts.txt";
	filesWriter.open(contacts_file, ofstream::app);
	for (int contactsCnt = 0; contactsCnt < added_contacts.size(); contactsCnt++)
	{
		

		if (filesWriter.is_open())
		{
			filesWriter << added_contacts[contactsCnt] << endl;
		}
		else
		{
			cout << "Error While saving session, Terminating..\n";
			exit(-1);
		}
		
	}
	filesWriter.clear();
	filesWriter.close();


	string favorite_messages_file = user_folder_path + "/favorite_messages.txt";
	writeType = ofstream::trunc;
	filesWriter.open(favorite_messages_file, writeType);
	while (!favorite_messages.empty())
	{
		
		
		if (filesWriter.is_open())
		{
			filesWriter << favorite_messages.front().getSenderId() << " " <<
				favorite_messages.front().getRecieverId() << " " <<
				favorite_messages.front().getMessageBody() << endl;

			favorite_messages.pop_front();

		}
		else
		{
			cout << "Error While saving session, Terminating..\n";
			exit(-1);
		}
		
	}
	filesWriter.clear();
	filesWriter.close();
}