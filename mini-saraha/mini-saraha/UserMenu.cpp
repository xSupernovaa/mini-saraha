#include "UserMenu.h"
#include <iostream>
#include "Server.h"
#include "WelcomeMenu.h"
using namespace std;

User* userP;
Server* serverP;
int id;
int contactID;

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

void sendMessage(tgui::TextArea::Ptr message, tgui::Label::Ptr sendPrompt, tgui::Button::Ptr send)
{
    if (!message->getText().toStdString().empty()) {
        sendPrompt->setVisible(true);
        Message messageS(userP->getID(), contactID, message->getText().toStdString());
        serverP->sendMessage(messageS);
        sendPrompt->setText("message sent");
    }
    else
    {
        sendPrompt->setVisible(true);
        sendPrompt->setText("please enter a message to send");
    }

}

void sendMesaageWidgets(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("sendMessage.txt");

    User selected_contact = *serverP->findUser(contactID);

    auto label = gui.get<tgui::Label>("Label2");
    label->setText(tgui::String(selected_contact.getUsername() + "\n" + to_string(selected_contact.getID())));

    auto sendPrompt = gui.get<tgui::Label>("Label3");
    sendPrompt->setVisible(false);

    auto send = gui.get<tgui::Button>("Button1");


    auto message = gui.get<tgui::TextArea>("TextArea1");


    send->onPress(&sendMessage, message, sendPrompt, send);

    auto back = gui.get<tgui::Button>("Button2");
    back->onPress([&] {UserMenu::backi(gui); });
}

void selectContact(tgui::ListBox::Ptr contactList)
{
    contactID = contactList->getSelectedItem().toInt();
}

void contactContactsWidgets(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("sent.txt");
    User selected_contact = *serverP->findUser(contactID);

    auto label = gui.get<tgui::Label>("Label1");
    label->setText(tgui::String("Contacts"));

    auto contactList = gui.get<tgui::ListBox>("messageList");


    auto undo = gui.get<tgui::Button>("Button1");
    if (userP->foundContacts()) {
        for (int i = 0; i < selected_contact.getContacts().size(); i++) {
            contactList->addItem(tgui::String(selected_contact.getContacts()[i]));
        }
    }
    else
    {
        undo->setEnabled(false);
        undo->setText(tgui::String("No contacts yet."));
    }

    contactList->setEnabled(false);

    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });

    auto undo = gui.get<tgui::Button>("Button1");
    undo->setVisible(false);
}


void UserChoiceWidgets(tgui::GuiBase& gui) {
     
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("receivedMessageChoice.txt");

    auto label = gui.get<tgui::Label>("Label1");
    label->setText(tgui::String("Contacts"));

    auto sendMessage = gui.get<tgui::Button>("all_messages");
    sendMessage->setText("Send Message");
    sendMessage->onPress([&] {sendMesaageWidgets(gui); });

    auto getcontacts = gui.get<tgui::Button>("user_messages");
    getcontacts->setText("View Contacts");
    getcontacts->onPress([&] {contactContactsWidgets(gui); });

    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });
}

void contactsWidgets(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("sent.txt");


    auto label = gui.get<tgui::Label>("Label1");
    label->setText(tgui::String("Contacts"));

    auto contactList = gui.get<tgui::ListBox>("messageList");


    auto undo = gui.get<tgui::Button>("Button1");
    undo->setVisible(false);
    if (userP->foundContacts()) {
        for (int i = 0; i < userP->getContacts().size(); i++) {
            contactList->addItem(tgui::String(userP->getContacts()[i]));
        }
    }
    else
    {
        undo->setEnabled(false);
        undo->setText(tgui::String("No contacts yet."));
    }

    contactList->onItemSelect(&selectContact, contactList);
    contactList->onItemSelect([&] {UserChoiceWidgets(gui); });

    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {UserMenu::backi(gui); });
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
    contacts->onPress([&] {contactsWidgets(gui); });

    auto logout = gui.get<tgui::Button>("logout");
    logout->onPress([&] {serverP->saveSession(); WelcomeMenu::backi(gui); });
}

void UserMenu::backi(tgui::GuiBase& gui)
{
    initial(gui);
}
