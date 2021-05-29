#include <iostream>
#include "Server.h"
#include "FilesManager.h"
#include "User.h"
#include <map>

using namespace std;
int main()
{
	User user(1,"bavlly", "1234");
	FilesManager file;
	map<string, pair<string, int>>  ret = file.load_users_credintials_from_disc();
	cout << ret["bavlly"].second;
}

