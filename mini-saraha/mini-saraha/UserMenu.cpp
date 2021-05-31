#include "UserMenu.h"
#include <iostream>
#include "Server.h"
using namespace std;

UserMenu::UserMenu(Server server) {
    serverP = &server;
    userP = server.get_Current_Logged_User();
}

void UserMenu::initial()
{
    cout << "------WELCOME TO YOUR ACCOUNT !" << endl;
    cout << "[1] My messages " << endl;
    cout << "[2] Sent messages " << endl;
    cout << "[3] favorites " << endl;
    cout << "[4] search  " << endl;
    cout << "[5] Contacts  " << endl;
    cout << "[6] log out   " << endl;

    cout << "------------------------------- " << endl;
    cout << "Your Choice : ";
    int userChoice;    cin >> userChoice;
    switch (userChoice) {
    case 1:
        
        break;

    case 2:
       
        break;

    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;

    default:
        break;

    }
    
}

void UserMenu::viewMessages( ) {

    userP->showrecievedMassages(); 
    cout << "----------------------" << endl;
    cout << "[1] Add Message To Favourite " << endl;
    cout << "[2] Back To Main Menu " << endl;
    int userChoice;    cin >> userChoice;
    switch (userChoice) {
    case 1:
        cout << "Choose Message :"; cin >> userChoice; 
      
    }
}
