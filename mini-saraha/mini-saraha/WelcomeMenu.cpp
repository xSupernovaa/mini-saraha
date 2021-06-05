#include "WelcomeMenu.h"
#include <iostream>
#include "Server.h"
#include "UserMenu.h"
using namespace std;

Server WelcomeMenu::server;
sf::RenderWindow window{ {800, 600}, "TGUI window with SFML" };
tgui::GuiSFML gui{ window };
void WelcomeMenu::welcome()
{
    server.loadSession();
    runExample(gui);
    gui.mainLoop();
}

void sign_up(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{

    WelcomeMenu::server.registerUser(username->getText().toStdString(), password->getText().toStdString());

}


void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{

    if (WelcomeMenu::server.login(username->getText().toStdString(), password->getText().toStdString()))
    {

        UserMenu menu(WelcomeMenu::server);
        menu.initial(gui);
    }
    else
    {
        cout << endl;
        cout << "Invalid email or password, please try again!" << endl;
    }

}


void updateTextSize(tgui::GuiBase& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.07f * windowHeight)); // 7% of height
}


void loginWidgets(tgui::GuiBase& gui)
{
    // Specify an initial text size instead of using the default value
    gui.removeAllWidgets();

    updateTextSize(gui);

    gui.loadWidgetsFromFile("login.txt");
    auto widgets = gui.getWidgets();
    auto editBoxUsername = gui.get<tgui::EditBox>("username");
    auto editBoxPassword = gui.get<tgui::EditBox>("pass");
    auto loginb = gui.get<tgui::Button>("login");
    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {WelcomeMenu::backi(gui); });
    loginb->onPress(&login, editBoxUsername, editBoxPassword);

}

void registerWidgets(tgui::GuiBase& gui)
{
    // Specify an initial text size instead of using the default value
    gui.removeAllWidgets();

    updateTextSize(gui);

    gui.loadWidgetsFromFile("login.txt");
    auto widgets = gui.getWidgets();
    auto editBoxUsername = gui.get<tgui::EditBox>("username");
    auto editBoxPassword = gui.get<tgui::EditBox>("pass");
    auto back = gui.get<tgui::Button>("back");
    back->onPress([&] {WelcomeMenu::backi(gui); });
    auto regb = gui.get<tgui::Button>("login");
    regb->setText("Register");
    regb->setPosition({ "35%", "70%" });
    regb->onPress(&sign_up, editBoxUsername, editBoxPassword);
}

void startUpWidgets(tgui::GuiBase& gui) {
    gui.removeAllWidgets();
    updateTextSize(gui);

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