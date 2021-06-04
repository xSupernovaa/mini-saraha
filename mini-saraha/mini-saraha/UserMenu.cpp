#include "UserMenu.h"
#include <iostream>
#include "Server.h"
using namespace std;

UserMenu::UserMenu(Server &server) {
    serverP = &server;
    userP = server.get_Current_Logged_User();
}

void UserMenu::initial()
{

    while (true)
    {
         system("CLS");
        cout << "------WELCOME TO YOUR ACCOUNT " << userP->getUsername() << endl;
        cout << "[1] My messages " << endl;
        cout << "[2] Sent messages " << endl;
        cout << "[3] favorites " << endl;
        cout << "[4] search  " << endl;
        cout << "[5] Contacts  " << endl;
        cout << "[6] log out   " << endl;

        cout << "------------------------------- " << endl;
        cout << "Your Choice : ";
        int userChoice;   
        cin >> userChoice;
        cin.ignore();
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
            viewContacts();
            break;

        case 6:
            //calling saveSession
            serverP->saveSession();
            return;

        default:
            break;

        }

        string pause;
        getline(cin,pause);
    }
}
    


void UserMenu::viewRecivedMessages( ) {
    if (userP->foundMessages())
    {
        serverP->viewMessages(userP->getID());
        cout << "----------------------" << endl;
        cout << "[1] Add Message To Favourite " << endl;
        cout << "[2] Back To Main Menu " << endl;
        cout << "----------------------" << endl;
        cout << "Your Choice : ";
        int userChoice;    cin >> userChoice;


        switch (userChoice) {
        case 1:
            cout << "Choose Message :"; cin >> userChoice;
            addToFavorite(userChoice);
            break;
        case 2:
            return;

        default:
            break;
        }
    }
    else
    {
        cout << "You don't have any messages" << endl; 
    }
}

void UserMenu::addToFavorite(int index)
{
    //since first message displayed is last message in array
    // and assuming user input is one based
    int size = userP->getRecievedMessages().size();
    int target = size - index; 
    
    serverP->addFavoriteMessage(userP->getReceivedMessage(target));
}




void UserMenu::viewSentMessages() {

    if (userP->foundSentMessages())
    {
        userP->showSentMassages();
        cout << "----------------------" << endl;
        cout << "[1] Undo last Message " << endl;
        cout << "[2] Back To Main Menu " << endl;
        cout << "----------------------" << endl;
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
    else {
        cout << "You don't have any messages" << endl;
    }
}




void UserMenu::viewFavouriteMessages() {

    
    if (userP->foundFavouriteMessages())
    {

        userP->showfavoriteMassages();
        cout << "----------------------" << endl;
        cout << "[1] Delete Oldest Favourite Message " << endl;
        cout << "[2] Back To Main Menu " << endl;
        cout << "------------------------------- " << endl;
        cout << "Your Choice : ";
        int userChoice;    cin >> userChoice;
        switch (userChoice) {
        case 1:
            serverP->delete_Last_Favorite_Message();
            break;
        case 2:
            return;

        default:
            break;


        }
    }
    else {
        cout << "You don't have any messages" << endl;
    }
}



void UserMenu::usersSearch() {

    int user_id; 
    cout << "------SEARCH-------" << endl;
    cout << "Enter user id : ";   cin >> user_id; 

    User *userS = serverP->findUser(user_id);

    if (userS != nullptr )
    {
        displayUserData(*userS);
        cout << "[1] Add to Conatcts " << endl;
        cout << "[2] Back To Main Menu " << endl;
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
    cout << "Username : " << user.getUsername()<< endl; 
    cout << "id : " << user.getID() << endl;
    cout << "------------------------" << endl;
}




void UserMenu::viewContacts() {
     
    if (userP->foundContacts())
    {


        cout << "------------------------" << endl;
        cout << "     Contacts  " << endl;
        cout << "------------------------" << endl;
        userP->showContacts();
        cout << "------------------------" << endl;
        cout << "[1] Select Contact  " << endl;
        cout << "[2] Back To Main Menu " << endl;
        cout << "------------------------" << endl;
        cout << "Your Choice : ";


        int userChoice;    cin >> userChoice;
        switch (userChoice)
        {
        case 1:
            selectContact();
            break;
        case 2:
            return;

        default:
            break;
        }
    }
}



void UserMenu::selectContact()
{
    cout << "Enter User id : ";
    int user_id;    cin >> user_id;
    User selected_contact = *serverP->findUser(user_id); 
        cout << "[1] Send Message:" << endl;
        cout << "[2] View Contacts :" << endl;
        cout << "------------------------" << endl;
        cout << "Your Choice : ";

        int userChoice;    cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            sendMessage(selected_contact);
            break;
        case 2:
            selected_contact.showContacts();
            cout << "[1]To main menu: ";
            cin >> userChoice; 
            return;

        default:
            break;
        }
    }
   




void UserMenu::sendMessage(User user)
{
    cout << "Tell "<< user.getUsername() << " anything!" << endl;
    string message; 
    cin >> message; 
    Message messageS(userP->getID(), user.getID(), message); 
    serverP->sendMessage(messageS);

}