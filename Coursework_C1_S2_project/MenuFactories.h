#pragma once

#include "Menu.h"
#include "MessageBus.h"
#include "AppCollections.h"

using namespace std;

class MainMenuFactory
{
public:
	static Menu makeMainMenu(AppCollections &AppCollections, MessageBus &messageBus);
};

class BookMenuFactory
{
public:
	static Menu makeBookMenu(AppCollections &AppCollections, MessageBus &messageBus, MenuCommand &goToMainMenu);
};

class LibrarianMenuFactory
{
public:
	static Menu makeLibrarianMenu(AppCollections &AppCollections, MessageBus &messageBus, MenuCommand &goToMainMenu);
};

class ReaderMenuFactory
{
public:
	static Menu makeReaderMenu(AppCollections &AppCollections, MessageBus &messageBus, MenuCommand &goToMainMenu);
};

class bookReservationMenuFactory
{
public:
	static Menu makeBookReservationMenu(AppCollections &AppCollections, MessageBus &messageBus, MenuCommand &goToMainMenu);
};
