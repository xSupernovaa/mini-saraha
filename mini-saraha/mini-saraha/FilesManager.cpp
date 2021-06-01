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



User FilesManager::load_user_instance_from_disc(int user_id)
{
	string user_folder_path = "data/users/user_" + to_string(user_id);
	
	string sent_messages_file = user_folder_path + "/sent_messages.txt";
	string received_messages_file = user_folder_path + "/received_messages.txt";
	string contacts_file = user_folder_path + "/contacts.txt";
	string favorite_messages_file = user_folder_path + "/favorite_messages.txt";
	string basic_data_file = user_folder_path + "/basic_data.txt";


	// Load messages in vectors
	vector <Message> sent_messages_vector = load_user_messages_from_disc(sent_messages_file);
	vector <Message> received_messages_vector = load_user_messages_from_disc(received_messages_file);
	vector <Message> favorite_messages_vector = load_user_messages_from_disc(favorite_messages_file);

	// move messages from vectors to suitable data structures
	stack<Message> sent_messages_stack = vector_to_stack(sent_messages_vector);
	stack<Message> received_messages_stack = vector_to_stack(received_messages_vector);
	deque<Message> favorite_messages_deque = vector_to_deque(favorite_messages_vector);


	vector<int> contacts = load_user_contants_from_disc(contacts_file);
	vector<string> basic_data = load_user_basic_data_from_disc(basic_data_file);

	User user(user_id, basic_data[0], basic_data[1], sent_messages_stack, received_messages_stack,
		favorite_messages_deque, contacts);

	return user; // تم بحمد الله
}


vector<Message> FilesManager::load_user_messages_from_disc(string messages_file_path)
{

	const char* messages_file_path_const = messages_file_path.c_str();

	vector<Message> messages;

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



stack<Message> FilesManager:: vector_to_stack(vector<Message> messages_vector)
{
	stack<Message> messages_stack;
	
	for (Message m : messages_vector)
		messages_stack.push(m);

	return messages_stack;
}

deque<Message> FilesManager:: vector_to_deque(vector<Message> messages_vector)
{
	deque<Message> messages_deque;

	for (Message m : messages_vector)
		messages_deque.push_back(m);

	return messages_deque;
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