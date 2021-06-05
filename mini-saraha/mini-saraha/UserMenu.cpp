#include "UserMenu.h"
#include <iostream>
#include "Server.h"
#include "WelcomeMenu.h"
using namespace std;

User* userP;
Server* serverP;
int id;

UserMenu::UserMenu(Server &server) {
    serverP = &server;
    userP = server.get_Current_Logged_User();
}

void addToFavorite(tgui::ListBox::Ptr messageList)
{
    int index = messageList->getSelectedItemIndex();
    //since first message displayed is last message in array
    // and assuming user input is one based
    int size = userP->getRecievedMessages().size();
    int target = size - index; 
    
    serverP->addFavoriteMessage(userP->getReceivedMessage(target));
}


void viewAllRecivedMessages(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("sent.txt");


    auto label = gui.get<tgui::Label>("Label1");
    label->setText(tgui::String("Received Messages"));

    auto messageList = gui.get<tgui::ListBox>("messageList");
    //add messages to list
    if (userP->foundMessages())
    {
        auto receivedMessages = userP->getRecievedMessages();
        int size = receivedMessages.size();
        while (!receivedMessages.empty()) {
            messageList->addItem(tgui::String(receivedMessages.back().getMessageBody()));
            receivedMessages.pop_back();
        }
        messageList->onItemSelect(&addToFavorite ,messageList);
    }
    else {
        messageList->addItem(tgui::String("You don't have any messages"));
    }


    //adding message to favorites
    auto addFavorite = gui.get<tgui::Button>("Button1");
    addFavorite->setEnabled(false);
    addFavorite->setText(tgui::String("Logic not done yet!"));

    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });
}


void recivedUserMessages(tgui::ListBox::Ptr messageList)
{
    int index = messageList->getSelectedItemIndex();
    id = messageList->getItemByIndex(index).toInt();
}

void senderMessagesWidgets(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("sent.txt");

    auto label = gui.get<tgui::Label>("Label1");
    label->setText(tgui::String("Received Messages"));

    vector<Message> messages = userP->showAllSenders(id);

    auto messageList2 = gui.get<tgui::ListBox>("messageList");
    //add messages to list
    for (int i = 0; i < messages.size(); i++)
    {
       messageList2->addItem(tgui::String(messages[i].getMessageBody()));
    }

    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });

    auto button = gui.get<tgui::Button>("Button1");
    button->setVisible(false);
   
}

void view_specific_user_messages(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("sent.txt");


    auto label = gui.get<tgui::Label>("Label1");
    label->setText(tgui::String("Received Messages"));

    auto messageList = gui.get<tgui::ListBox>("messageList");
    //add messages to list
    if (userP->foundMessages())
    {
        auto receivedMessages = userP->getRecievedMessages();
        int size = receivedMessages.size();
        while (!receivedMessages.empty()) {
            messageList->addItem(tgui::String(receivedMessages.back().getSenderId()));
            receivedMessages.pop_back();
        }
        messageList->onItemSelect(&recivedUserMessages, messageList);
        messageList->onItemSelect([&] {senderMessagesWidgets(gui); });
    }
    else {
        messageList->addItem(tgui::String("You don't have any messages from users"));
    }

    auto button = gui.get<tgui::Button>("Button1");
    button->setVisible(false);

    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });
}



void receivedMessagesWidgets(tgui::GuiBase& gui)
{
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("receivedMessageChoice.txt");

    auto viewAllMessages = gui.get<tgui::Button>("all_messages");
    viewAllMessages->onPress([&] {viewAllRecivedMessages(gui); });

    auto viewFromUserMessages = gui.get<tgui::Button>("user_messages");
    viewFromUserMessages->onPress([&] {view_specific_user_messages(gui); });

    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });
}   



void viewSentMessages(tgui::ListBox::Ptr messageList) {

    if (userP->foundSentMessages())
    {
        auto sentMessages = userP->getSentMessages();
        int size = sentMessages.size();
        while(!sentMessages.empty()) {
            messageList->addItem(tgui::String(sentMessages.back().getMessageBody()));
            sentMessages.pop_back();
        }
    }
    else {
        messageList->addItem(tgui::String("You don't have any messages"));
    }
}

void sentMessagesWidgets(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("sent.txt");

    auto messageList = gui.get<tgui::ListBox>("messageList");
    viewSentMessages(messageList);

    auto undo = gui.get<tgui::Button>("Button1");
    if (serverP->isMessageDeletion)
        undo->onPress([&] {serverP->deleteLastMessage(); });
    else
    {
        undo->setEnabled(false);
        undo->setText(tgui::String("No messages sent this session."));
    }

    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });
}



void viewFavouriteMessages() {

    
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

void viewFavoriteMessages(tgui::ListBox::Ptr messageList)
{
    if (userP->foundFavouriteMessages())
    {
        auto fav_messages = userP->getFavoriteMessages();
        int size = fav_messages.size();
        while (!fav_messages.empty())
        {
            messageList->addItem(tgui::String(fav_messages.back().getMessageBody()));
            fav_messages.pop_back();
        }
    }
    else {
        messageList->addItem(tgui::String("You don't have any messages"));
    }
}

void favoriteMessagesWidgets(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("sent.txt");


    auto label = gui.get<tgui::Label>("Label1");
    label->setText(tgui::String("Favorite Messages"));
    
    auto messageList = gui.get<tgui::ListBox>("messageList");
    viewFavoriteMessages(messageList);

    auto undo = gui.get<tgui::Button>("Button1");
    if (userP->foundFavouriteMessages())
        undo->onPress([&] {serverP->delete_Last_Favorite_Message(); });
    else
    {
        undo->setEnabled(false);
        undo->setText(tgui::String("No favorite messages yet."));
    }

    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });
}




void displayUserData(User  user) {

    cout << "------------------------" << endl;
    cout << "Username : " << user.getUsername()<< endl; 
    cout << "id : " << user.getID() << endl;
    cout << "------------------------" << endl;
}

void usersSearch(tgui::EditBox::Ptr id, tgui::Label::Ptr result, tgui::Button::Ptr add) {
    
    int user_id = id->getText().toInt();
    /*cout << "------SEARCH-------" << endl;
    cout << "Enter user id : ";   cin >> user_id;*/ 

    User *userS = serverP->findUser(user_id);
    if (userS != nullptr) {
        add->setVisible(true);
        result->setText(userS->getUsername()+ "#" + to_string(userS->getID()));
        add->onPress([&] { serverP->addContact(userS->getID()); });
    }
    else {
        result->setText("No user with this id");
        add->setVisible(false);
    }
 
}

void searchWidgets(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("search.txt");

    auto searchBox = gui.get<tgui::EditBox>("search");
    auto result = gui.get<tgui::Label>("screen");
    auto addContact = gui.get<tgui::Button>("Button1");
    addContact->setVisible(false);
    searchBox->onReturnKeyPress(&usersSearch, searchBox, result, addContact);
    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });
}

void sendMessage(User user)
{
    cout << "Tell "<< user.getUsername() << " anything!" << endl;
    string message; 
    cin >> message; 
    Message messageS(userP->getID(), user.getID(), message);
    serverP->sendMessage(messageS);

}



void selectContact()
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
   



void viewContacts() {
     
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


void UserMenu::initial(tgui::GuiBase& gui)
{
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("user.txt");
    auto widgets = gui.getWidgets();
    auto label = gui.get<tgui::Label>("label");
    label->setText("WELCOME TO YOUR ACCOUNT " + userP->getUsername());

    auto myMessages = gui.get<tgui::Button>("my_messages");
    myMessages->onPress([&] {receivedMessagesWidgets(gui); });

    auto sent = gui.get<tgui::Button>("sent");
    sent->onPress([&] {sentMessagesWidgets(gui); });

    auto fav = gui.get<tgui::Button>("fav");
    fav->onPress([&] {favoriteMessagesWidgets(gui); });

    auto search = gui.get<tgui::Button>("search");
    search->onPress([&] {searchWidgets(gui); });

    auto contacts = gui.get<tgui::Button>("contacts");
    contacts->onPress(&viewContacts);

    auto logout = gui.get<tgui::Button>("logout");
    logout->onPress([&] {serverP->saveSession(); WelcomeMenu::backi(gui); });
}

void UserMenu::backi(tgui::GuiBase& gui)
{
    initial(gui);
}
