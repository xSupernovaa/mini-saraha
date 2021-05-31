#include "WelcomeMenu.h"
#include <iostream>
#include "Server.h"
#include "UserMenu.h"
using namespace std;

void WelcomeMenu::welcome()
{

        server.loadSession();

        while (true)
        {
            cout << endl;
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
                return;

            default:

                cout << "invalid choice ,please try again " << endl;
            }

        }
    
}

void WelcomeMenu::sign_up()
{
    string username, password;
    cout << "----------  Sign up ------------ " << endl;
    cout << "Enter Your User Name " << endl;
    cin >> username;
    cout << "Enter Your Password " << endl;
    cin >> password;
   
    server.registerUser(username, password);
    
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
     UserMenu menu(server) ;
      menu.initial();
    }
    else
    {
       cout << endl; 
        cout << "Invalid email or password, please try again!" << endl;
    }

}

