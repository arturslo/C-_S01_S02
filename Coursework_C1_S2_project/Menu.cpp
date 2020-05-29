#include <functional>
#include <vector>
#include <iostream>
#include <string>

#include "Menu.h"

using namespace std;

MenuCommand::MenuCommand(const string& title, const function<bool()> lambda)
{
	this->title = title;
	this->lambda = lambda;
}

string MenuCommand::getTitle()
{
	return title;
}

bool MenuCommand::execute()
{
	return this->lambda();
}

Menu::Menu(int id, string title)
{
	this->id = id;
	this->title = title;
}

int Menu::getId()
{
	return this->id;
}

void Menu::addMenuCommand(const MenuCommand command)
{
	this->menuCommands.push_back(command);
}

void Menu::print()
{
	cout << this->title << endl;
	cout << endl;

	for (size_t i = 0; i != menuCommands.size(); i++)
	{
		cout << i << ": " << menuCommands[i].getTitle() << endl;
	}
}

bool Menu::isValidCommandIndex(const int commandIndex)
{
	try
	{
		this->menuCommands.at(commandIndex);
	}
	catch (const out_of_range& oor)
	{
		return false;
	}

	return true;
}

bool Menu::executeCommand(const int commandIndex)
{
	return menuCommands.at(commandIndex).execute();
}
