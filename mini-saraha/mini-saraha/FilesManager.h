#pragma once
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include "User.h"
#include <direct.h>

using namespace std;

class FilesManager
{
public:
	    map<string, pair<string, int>> load_users_credintials_from_disc();
		void add_new_user_instance_to_disc(User new_user);
		User load_user_instance_from_disc(int user_id);
		//void add_user_data_to_disk(User user);
		void add_user_data_to_disk(int logged_user_id,
								   bool isMessageDeletion,
								   queue<Message> &sent_messages,
								   deque<Message> &favorite_messages,
								   vector<int> &added_contacts);

private:
	ofstream filesWriter;
	ifstream filesReader;
	string make_new_user_folder(string folder_name);
	void add_new_user_credintials_to_disc(string username, string password, int id);
	void create_new_user_data_files(string folder_path);
	void create_new_user_file(string file_path);
	vector<Message> load_user_messages_from_disc(string user_folder_path);
	vector<int> load_user_contants_from_disc(string user_folder_path);
	queue<Message> vector_to_queue(vector<Message> messages_vector);
	deque<Message> vector_to_deque(vector<Message> messages_vector);
	vector<string> load_user_basic_data_from_disc(string basic_data_file);
};

