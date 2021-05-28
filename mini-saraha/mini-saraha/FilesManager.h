#pragma once
#include <fstream>
#include <map>
#include <string>
#include <iostream>
using namespace std;
class FilesManager
{
public:
		map<string, string> load_users_credintials_from_disc();
		void add_new_user_credintials_to_disc(string username, string password);

private:
	ofstream filesWriter;
	ifstream filesReader;

};

