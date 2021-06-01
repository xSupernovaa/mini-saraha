#include <iostream>

#include "FilesManager.h"
#include "User.h"
#include <map>
#include "WelcomeMenu.h"
#include "FilesManager.h"
using namespace std;
int main()
{
	/*FilesManager fmgr;
	User user = fmgr.load_user_instance_from_disc(0);

	user.showContacts();
	user.showSentMassages();
	user.showrecievedMassages();*/

	WelcomeMenu W;
    W.welcome();

}

