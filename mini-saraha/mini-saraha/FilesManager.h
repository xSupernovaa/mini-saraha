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
		map<string, string> load_users_credintials_from_disc();
		void add_new_user_instance_to_disc(User new_user);
private:
	ofstream filesWriter;
	ifstream filesReader;
	string make_new_user_folder(string folder_name);
	void add_new_user_credintials_to_disc(string username, string password);
	void create_new_user_data_files(string folder_path);

};

