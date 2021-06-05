#pragma once
#include "Server.h"
#include <TGUI/TGUI.hpp> 
class WelcomeMenu
{
public:
	static Server server;
	 void welcome();
	 bool runExample(tgui::GuiBase& gui);
	 static void backi(tgui::GuiBase& gui);
};

