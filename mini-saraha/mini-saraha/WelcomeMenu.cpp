#include "WelcomeMenu.h"
#include <iostream>
#include "Server.h"
#include "UserMenu.h"
using namespace std;

void WelcomeMenu::welcome()
{

   
    cout << "------WELCOME TO SARAHAH!------" << endl;
    cout << "What would you like to do ? " << endl;
    cout << "[1] Sign up " << endl;
    cout << "[2] Sign in " << endl;
    cout << "[3] Exit " << endl;
    cout << "------------------------------- " << endl;
    cout << "Your Choice : ";
    int userChoice;    cin >> userChoice;
    switch (userChoice) {

    case 1:
       sign_up();
        break;

    case 2:
        sign_in();
        break;

    case 3:
        break;

    default:
        cout << "invalid choice ,please try again " << endl;
        welcome();

    }


}

void WelcomeMenu::sign_up()
{
    string username, password;
    cout << "----------  Sign up ------------ " << endl;
    cout << "Enter Your Name " << endl;
    cin >> username;
    cout << "Enter Your Password " << endl;
    cin >> password;
    // REGISTER USER 
    bool flag = server.registerUser(username, password);
    if (!flag) {
        system("CLS");
        sign_up();
    }
    sign_in();
}

void WelcomeMenu::sign_in()
{
    string username, password;
    cout << "----------  Sign in  ------------ " << endl;
    cout << "Enter Your Name " << endl;
    cin >> username;
    cout << "Enter Your Password " << endl;
    cin >> password;
   if (server.login(username, password))
    {
        UserMenu menu(server);
    }
    else
    {
        cout << "Invalid email or password, please try again!" << endl;
    }

}

