#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "DataStructures.h"
#include "Menu.h"
#include "MessageBus.h"
#include "ConsoleApp.h"
#include "ReadWrite.h"
#include "MenuFactories.h"
#include "AppCollections.h"

using namespace std;

/*
. Bibliotēka. Objektu un to īpašību piemēri: grāmata (kods, nosaukums, autors, izdošanas gads,
temats u.c.), lasītājs (kods, uzvārds, vārds, grāmatas paņemšanas datums, grāmatas atdošanas
datums u.c.), bibliotekārs u.tml.

*/

int main()
{
	vector<Book> books;
	vector<Librarian> librarians;
	vector<Reader> readers;
	vector<BookReservation> bookReservations;

	readFromFile(books);
	readFromFile(librarians);
	readFromFile(readers);
	readFromFile(bookReservations);

	AppCollections appCollections = AppCollections(books, librarians, readers, bookReservations);
	MessageBus messageBus = MessageBus();

	MenuCommand goToMainMenu = MenuCommand("go to main menu", [&messageBus]() mutable
	{
		messageBus.notify(Message(Message::LOAD_MENU, to_string(Menu::MAIN_MENU)));
		return true;
	}
	);

	Menu mainMenu = MainMenuFactory::makeMainMenu(appCollections, messageBus);
	Menu bookMenu = BookMenuFactory::makeBookMenu(appCollections, messageBus, goToMainMenu);
	Menu librarianMenu = LibrarianMenuFactory::makeLibrarianMenu(appCollections, messageBus, goToMainMenu);
	Menu readerMenu = ReaderMenuFactory::makeReaderMenu(appCollections, messageBus, goToMainMenu);
	Menu bookReservationMenu = bookReservationMenuFactory::makeBookReservationMenu(appCollections, messageBus, goToMainMenu);

	ConsoleApp consoleApp;
	messageBus.addListener(&consoleApp);
	consoleApp.setCurrentMenu(mainMenu);
	consoleApp.addMenu(mainMenu);
	consoleApp.addMenu(bookMenu);
	consoleApp.addMenu(librarianMenu);
	consoleApp.addMenu(readerMenu);
	consoleApp.addMenu(bookReservationMenu);
	consoleApp.run();

	return 0;
}
