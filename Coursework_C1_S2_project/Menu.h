#pragma once

#include <functional>
#include <vector>
#include <string>

using namespace std;

class MenuCommand
{
private:
	string title;
	function<bool()> lambda;
public:
	MenuCommand(const string& title, const function<bool()> lambda);
	string getTitle();
	bool execute();
};

class Menu
{
private:
	int id;
	string title;
	vector<MenuCommand> menuCommands;

public:
	static const int MAIN_MENU = 1;
	static const int BOOK_MENU = 2;
	static const int LIBRARIAN_MENU = 3;
	static const int READER_MENU = 4;
	static const int BOOK_RESERVATION_MENU = 5;

	Menu() = default;
	Menu(int id, string title);
	int getId();
	void addMenuCommand(const MenuCommand command);
	void print();
	bool isValidCommandIndex(const int commandIndex);
	bool executeCommand(const int commandIndex);
};
