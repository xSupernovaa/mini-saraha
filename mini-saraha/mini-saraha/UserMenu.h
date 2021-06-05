#pragma once
#include "User.h"
#include "Server.h"
#include <TGUI/TGUI.hpp>
class UserMenu
{
	
public:
	UserMenu(Server &server);
	static void initial(tgui::GuiBase& gui);
	static void backi(tgui::GuiBase& gui);
};

