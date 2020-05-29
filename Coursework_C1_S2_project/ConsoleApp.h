#pragma once

#include <map>
#include "Menu.h"
#include "MessageBus.h"

using namespace std;

class ConsoleApp : public ListenerInterface
{
private:
	map<int, Menu> menus;
	Menu currentMenu;
	bool exitApp = false;

public:
	ConsoleApp() = default;
	virtual void onNotify(Message message);
	void addMenu(Menu menu);
	void setCurrentMenu(Menu currentMenu);
	void run();
};
