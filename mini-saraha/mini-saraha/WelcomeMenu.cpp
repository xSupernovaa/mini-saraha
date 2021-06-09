#include "WelcomeMenu.h"
#include <iostream>
#include "Server.h"
#include "UserMenu.h"
using namespace std;

Server WelcomeMenu::server;
sf::RenderWindow window{ {800, 600}, "TGUI window with SFML" };
tgui::GuiSFML gui{ window };
bool registered = false;

void WelcomeMenu::welcome()
{
    server.loadSession();
    runExample(gui);
    gui.mainLoop();
}




void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::Label::Ptr pPrompt)
{

    if (WelcomeMenu::server.login(username->getText().toStdString(), password->getText().toStdString()))
    {

        UserMenu menu(WelcomeMenu::server);
        menu.initial(gui);
    }
    else
    {
        pPrompt->setVisible(true);
        pPrompt->setText("Invalid email or password, please try again!");
    }

}


void loginWidgets(tgui::GuiBase& gui)
{
    // Specify an initial text size instead of using the default value
    gui.removeAllWidgets();


    gui.loadWidgetsFromFile("login.txt");
    auto widgets = gui.getWidgets();
    auto editBoxUsername = gui.get<tgui::EditBox>("username");
    auto editBoxPassword = gui.get<tgui::EditBox>("pass");
    auto ePrombt = gui.get<tgui::Label>("eprombt");
    auto pPrombt = gui.get<tgui::Label>("prombt");
    ePrombt->setVisible(false);
    pPrombt->setVisible(false);

    auto loginb = gui.get<tgui::Button>("login");
    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {WelcomeMenu::backi(gui); });
    loginb->onPress(&login, editBoxUsername, editBoxPassword, pPrombt);

}

void sign_up(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::Label::Ptr ePrombt, tgui::Label::Ptr pPrombt, tgui::Button::Ptr regb)
{
    bool flag = WelcomeMenu::server.registerUser(username->getText().toStdString(), password->getText().toStdString());
    if (!flag) {
        ePrombt->setVisible(true);
        pPrombt->setVisible(true);
        ePrombt->setText("Username is already taken, enter a username with at least 5 characters");
        pPrombt->setText("Please enter a password with at least on upper case, one lower case, one digit, one special character, minimum eight in length");
    }
    else {
        pPrombt->setVisible(true);
        pPrombt->setText("registered successfully");
        regb->setEnabled(false);
        ePrombt->setVisible(false);
    }
}

void registerWidgets(tgui::GuiBase& gui)
{
    // Specify an initial text size instead of using the default value
    gui.removeAllWidgets();


    gui.loadWidgetsFromFile("login.txt");
    auto widgets = gui.getWidgets();
    auto editBoxUsername = gui.get<tgui::EditBox>("username");
    auto editBoxPassword = gui.get<tgui::EditBox>("pass");
    auto ePrombt = gui.get<tgui::Label>("eprombt");
    auto pPrombt = gui.get<tgui::Label>("prombt");
    ePrombt->setVisible(false);
    pPrombt->setVisible(false);
    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {WelcomeMenu::backi(gui); });
    auto regb = gui.get<tgui::Button>("login");
    regb->setText("Register");
    regb->setPosition({ "35%", "75%" });
    regb->onPress(&sign_up, editBoxUsername, editBoxPassword, ePrombt, pPrombt, regb);
}

void startUpWidgets(tgui::GuiBase& gui) {
    gui.removeAllWidgets();

    gui.loadWidgetsFromFile("startup.txt");

    gui.get("register")->getSignal("Pressed").connect([&] {registerWidgets(gui); });
    gui.get("login")->getSignal("Pressed").connect([&] {loginWidgets(gui); });
    gui.get("exit")->getSignal("Pressed").connect([&] {window.close(); });

}

bool WelcomeMenu::runExample(tgui::GuiBase& gui)
{
    try
    {
        startUpWidgets(gui);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

void WelcomeMenu::backi(tgui::GuiBase& gui) {
    startUpWidgets(gui);
}