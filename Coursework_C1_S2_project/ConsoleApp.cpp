#include "ConsoleApp.h"
#include "Menu.h"
#include "MessageBus.h"
#include "Input.h"

#include <iostream>
#include <map>

using namespace std;

void ConsoleApp::onNotify(Message message)
{
	if (message.getType() == Message::LOAD_MENU)
	{
		int menuId = stoi(message.getData());
		currentMenu = menus.at(menuId);
	}
	else if (message.getType() == Message::EXIT_APP)
	{
		exitApp = true;
	}
}

void ConsoleApp::addMenu(Menu menu)
{
	this->menus.insert({ menu.getId(), menu });
}

void ConsoleApp::setCurrentMenu(Menu currentMenu)
{
	this->currentMenu = currentMenu;
}

void ConsoleApp::run()
{
	int commandIndex = 0;
	bool isCommandIndexInt = false;
	bool isComandIndexFound = false;

	while (!exitApp)
	{
		do
		{
			currentMenu.print();
			cout << endl;
			cout << "Choose command: ";
			isCommandIndexInt = Input::readInt(commandIndex);
			isComandIndexFound = currentMenu.isValidCommandIndex(commandIndex);
		} while (!isCommandIndexInt || !isComandIndexFound);

		// TODO execution can fail
		currentMenu.executeCommand(commandIndex);
	}
}
