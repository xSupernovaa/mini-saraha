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

    while (true)
    {
        system("CLS");
        cout << "------WELCOME TO YOUR ACCOUNT " << endl;
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
            viewRecivedMessages();
            break;

        case 2:
            viewSentMessages();
            break;

        case 3:
            viewFavouriteMessages();
            break;
        case 4:
            usersSearch();
            break;
        case 5:

            break;
        case 6:
            return;

        default:
            break;

        }
    }
}
    


void UserMenu::viewRecivedMessages( ) {

    serverP->viewMessages(userP->getID()); 
    cout << "----------------------" << endl;
    cout << "[1] Add Message To Favourite " << endl;
    cout << "[2] Back To Main Menu " << endl;
    int userChoice;    cin >> userChoice;
    switch (userChoice) {
    case 1:
        cout << "Choose Message :"; cin >> userChoice; 
    //    userP->addToFavorite(userP->getLastMessage); 
    //    waiting for bavly changes 
        break;
    case 2:
        return;

    default:
        break;
    

    }
}


void UserMenu::viewSentMessages() {
    //display sent messages 
   // serverP.
    // 
    cout << "----------------------" << endl;
    cout << "[1] Undo last Message " << endl;
    cout << "[2] Back To Main Menu " << endl;
    int userChoice;    cin >> userChoice;
    switch (userChoice) {
    case 1:
        serverP->deleteLastMessage();
        break;
    case 2:
        return; 
    default:
        break;


    }
}


void UserMenu::viewFavouriteMessages() {

  //    ->viewFavouriteMessages() ;   Not Created Yet  
    cout << "----------------------" << endl;
    cout << "[1] Delete Last Favourite Message " << endl;
    cout << "[2] Back To Main Menu " << endl;
    cout << "------------------------------- " << endl;
    cout << "Your Choice : ";
    int userChoice;    cin >> userChoice;
    switch (userChoice) {
    case 1:
        serverP->deleteLastMessage();
        break;
    case 2:
        return;

    default:
        break;


    }
}

void UserMenu::usersSearch() {

    int user_id; 
    cout << "------SEARCH-------" << endl;
    cout << "Enter user id";   cin >> user_id; 
    User *userS = serverP->findUser(user_id);
    if (userS != nullptr)
    {
        displayUserData(*userS);
        cout << "[1] Add to Conatcts :" << endl;
        cout << "[2] Back To Main Menu :" << endl;
        cout << "------------------------------- " << endl;
        cout << "Your Choice : ";
        int userChoice;    cin >> userChoice;
        switch (userChoice)
        {
        case 1 :
            serverP->addContact(userS->getID()); 
            break;
        case 2:
            return; 

        default:
            break;
        }

    }
   
}


void UserMenu::displayUserData(User  user) {
    cout << "------------------------" << endl;
    cout << "Username : " << user.getUsername(); 
    cout << "id : " << user.getID();
    cout << "------------------------" << endl;

}

