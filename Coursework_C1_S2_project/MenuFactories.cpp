#include <iostream>
#include <vector>
#include "MenuFactories.h"
#include "DataStructures.h"
#include "Menu.h"
#include "MessageBus.h"
#include "Input.h"
#include "ReadWrite.h"

using namespace std;

Menu MainMenuFactory::makeMainMenu(AppCollections &appCollections, MessageBus &messageBus)
{
	Menu mainMenu = Menu(Menu::MAIN_MENU, "Main Menu");

	MenuCommand goToBookMenu = MenuCommand("go to book menu", [&messageBus]() mutable
	{
		messageBus.notify(Message(Message::LOAD_MENU, to_string(Menu::BOOK_MENU)));
		return true;
	}
	);

	MenuCommand goToLibrarianMenu = MenuCommand("go to librarian menu", [&messageBus]() mutable
	{
		messageBus.notify(Message(Message::LOAD_MENU, to_string(Menu::LIBRARIAN_MENU)));
		return true;
	}
	);

	MenuCommand goToReaderMenu = MenuCommand("go to reader menu", [&messageBus]() mutable
	{
		messageBus.notify(Message(Message::LOAD_MENU, to_string(Menu::READER_MENU)));
		return true;
	}
	);

	MenuCommand goToBookReservationrMenu = MenuCommand("go to book reservation menu", [&messageBus]() mutable
	{
		messageBus.notify(Message(Message::LOAD_MENU, to_string(Menu::BOOK_RESERVATION_MENU)));
		return true;
	}
	);

	MenuCommand exitApp = MenuCommand("exit", [&messageBus, &appCollections]() mutable
	{
		writeToFile(appCollections.books);
		writeToFile(appCollections.librarians);
		writeToFile(appCollections.readers);
		writeToFile(appCollections.bookReservations);
		messageBus.notify(Message(Message::EXIT_APP, ""));
		return true;
	}
	);

	mainMenu.addMenuCommand(goToBookMenu);
	mainMenu.addMenuCommand(goToLibrarianMenu);
	mainMenu.addMenuCommand(goToReaderMenu);
	mainMenu.addMenuCommand(goToBookReservationrMenu);
	mainMenu.addMenuCommand(exitApp);

	return mainMenu;
}

Menu BookMenuFactory::makeBookMenu(AppCollections &appCollections, MessageBus &messageBus, MenuCommand &goToMainMenu)
{
	Menu bookMenu = Menu(Menu::BOOK_MENU, "Book Menu");
	MenuCommand addBook = MenuCommand("add book", [&messageBus, &appCollections]() mutable
	{
		Book newBook;
		bool inputResult = false;

		while (!inputResult)
		{
			cout << "book code[10]: " << endl;
			inputResult = Input::readCode(newBook.code, 10, appCollections.books);
		}
		inputResult = false;

		while (!inputResult)
		{
			cout << "book title[50]: " << endl;
			inputResult = Input::readLine(newBook.title, 50);
		}

		inputResult = false;

		while (!inputResult)
		{
			cout << "book author[50]: " << endl;
			inputResult = Input::readLine(newBook.author, 50);
		}

		inputResult = false;

		while (!inputResult)
		{
			cout << "book yearOfIssue[number]: " << endl;
			inputResult = Input::readInt(newBook.yearOfIssue);
		}

		inputResult = false;

		while (!inputResult)
		{
			cout << "book genre[50]: " << endl;
			inputResult = Input::readLine(newBook.genre, 20);
		}

		inputResult = false;

		appCollections.books.push_back(newBook);

		return true;
	}
	);

	MenuCommand printBooks = MenuCommand("print books", [&messageBus, &appCollections]() mutable
	{

		if (appCollections.books.size() == 0)
		{
			cout << "No books!" << endl;
			return true;
		}

		for (auto book : appCollections.books)
		{
			book.print();
			cout << endl;
		}

		return true;
	}
	);

	MenuCommand editBook = MenuCommand("edit book", [&messageBus, &appCollections]() mutable
	{
		int choice = -1;
		bool isInputCorrect = false;
		Book* book = NULL;

		const int BACK = 0;
		const int SET_BOOK_TO_EDIT = 1;
		const int EDIT_CODE = 2;
		const int EDIT_TITLE = 3;
		const int EDIT_AUTHOR = 4;
		const int EDIT_YEAR_OF_ISSUE = 5;
		const int EDIT_GENRE = 6;

		do
		{
			if (book != NULL)
			{
				cout << "book to edit:" << endl;
				book->print();
				cout << endl;
			}

			cout << endl;
			cout << BACK << ": back" << endl;
			cout << SET_BOOK_TO_EDIT  << ": set book to edit" << endl;
			cout << EDIT_CODE << ": edit code" << endl;
			cout << EDIT_TITLE << ": edit title" << endl;
			cout << EDIT_AUTHOR << ": edit author" << endl;
			cout << EDIT_YEAR_OF_ISSUE << ": edit year of issue" << endl;
			cout << EDIT_GENRE << ": edit genre" << endl;
			cout << endl;

			cout << "input choice: ";
			isInputCorrect = Input::readInt(choice);
			if (!isInputCorrect)
			{
				choice = -1;
			}

			if (choice == SET_BOOK_TO_EDIT)
			{
				char code[10];
				cout << "book code: ";
				bool inputResult = Input::readLine(code, 10);
				if (inputResult)
				{
					int index = findIndexByCode(appCollections.books, code);
					if (index == -1)
					{
						cout << "book not found" << endl;
						book = NULL;
					}
					else
					{
						book = &appCollections.books[index];
					}
				}
				else
				{
					cout << "bad input" << endl;
				}
			}
			else if (choice == EDIT_CODE)
			{
				if (book != NULL)
				{
					int charSize = size(book->code);
					char* newValue = new char[charSize]();
					char* oldValue = new char[charSize]();
					cout << "new code: ";
					bool inputResult = Input::readCode(newValue, charSize, appCollections.books);
					if (inputResult)
					{
						strcpy_s(oldValue, charSize, book->code);
						strcpy_s(book->code, charSize, newValue);
						
						for (auto bookReservation : appCollections.bookReservations)
						{
							if (strcmp(bookReservation.bookCode, oldValue) == 0)
							{
								strcpy_s(bookReservation.bookCode, charSize, newValue);
							}
						}
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no book set" << endl;
				}
			}
			else if (choice == EDIT_TITLE)
			{
				if (book != NULL)
				{
					int charSize = size(book->title);
					char* newValue = new char[charSize]();
					cout << "new title: ";
					bool inputResult = Input::readLine(newValue, charSize);
					if (inputResult)
					{
						strcpy_s(book->title, charSize, newValue);
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no book set" << endl;
				}

			}
			else if (choice == EDIT_AUTHOR)
			{
				if (book != NULL)
				{
					int charSize = size(book->author);
					char* newValue = new char[charSize]();
					cout << "new author: ";
					bool inputResult = Input::readLine(newValue, charSize);
					if (inputResult)
					{
						strcpy_s(book->author, charSize, newValue);
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no book set" << endl;
				}

			}
			else if (choice == EDIT_YEAR_OF_ISSUE)
			{
				if (book != NULL)
				{
					int newValue;
					cout << "new yearOfIssue: ";
					bool inputResult = Input::readInt(newValue);
					if (inputResult)
					{
						book->yearOfIssue = newValue;
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no book set" << endl;
				}

			}
			else if (choice == EDIT_GENRE)
			{
				if (book != NULL)
				{
					int charSize = size(book->genre);
					char* newValue = new char[charSize]();
					cout << "new genre: ";
					bool inputResult = Input::readLine(newValue, charSize);
					if (inputResult)
					{
						strcpy_s(book->genre, charSize, newValue);
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no book set" << endl;
				}
			}
		}
		while (choice != BACK);

		return true;
	}
	);

	MenuCommand searchBooksByYear = MenuCommand("search books by issue year", [&messageBus, &appCollections]() mutable
	{
		int choice = -1;
		bool isInputCorrect = false;
		bool isYearInputCorrect = false;
		int searchYear = 0;

		const int BACK = 0;
		const int SET_YEAR_TO_SEARCH = 1;
		const int PRINT_BOOKS = 2;
		const int DELETE_BOOKS = 3;

		do
		{
			cout << endl;
			cout << BACK << ": back" << endl;
			cout << SET_YEAR_TO_SEARCH << ": set issue year to search" << endl;
			cout << PRINT_BOOKS << ": print books" << endl;
			cout << DELETE_BOOKS << ": delete books" << endl;
			cout << endl;

			cout << "input choice: ";
			isInputCorrect = Input::readInt(choice);
			if (!isInputCorrect)
			{
				choice = -1;
			}

			if (choice == SET_YEAR_TO_SEARCH)
			{
				cout << "book issue year: ";
				isYearInputCorrect = Input::readInt(searchYear);
				if (isYearInputCorrect)
				{
					cout << "found books: " << countBooksByYear(searchYear, appCollections.books) << endl << endl;
				}
				else
				{
					cout << "bad input" << endl;
				}
			}
			else if (choice == PRINT_BOOKS)
			{
				if (isYearInputCorrect)
				{
					cout << endl;
					printBooksByYear(searchYear, appCollections.books);
					cout << endl;
				}
				else
				{
					cout << "no issue year set" << endl;
				}
			}
			else if (choice == DELETE_BOOKS)
			{
				if (isYearInputCorrect)
				{
					deleteBooksByYear(searchYear, appCollections.books, appCollections.bookReservations);
					isYearInputCorrect = false;
				}
				else
				{
					cout << "no issue year set" << endl;
				}
			}

		}
		while (choice != BACK);

		return true;
	}
	);

	MenuCommand printOrderedByIssueYear = MenuCommand("print ordered by issue year", [&messageBus, &appCollections]() mutable
	{
		vector<Book> orderedBooks = booksOrderedByIssueYear(appCollections.books);

		if (orderedBooks.size() == 0)
		{
			cout << "no books" << endl;
			cout << endl;
		}

		for (auto book : orderedBooks)
		{
			book.print();
			cout << endl;
		}

		return true;
	}
	);

	bookMenu.addMenuCommand(goToMainMenu);
	bookMenu.addMenuCommand(addBook);
	bookMenu.addMenuCommand(printBooks);
	bookMenu.addMenuCommand(editBook);
	bookMenu.addMenuCommand(searchBooksByYear);
	bookMenu.addMenuCommand(printOrderedByIssueYear);

	return bookMenu;
}

Menu LibrarianMenuFactory::makeLibrarianMenu(AppCollections &appCollections, MessageBus &messageBus, MenuCommand &goToMainMenu)
{
	Menu librarianMenu = Menu(Menu::LIBRARIAN_MENU, "Librarian Menu");

	MenuCommand addLibrarian = MenuCommand("add librarian", [&messageBus, &appCollections]() mutable
	{
		Librarian librarian;
		bool inputResult = false;

		while (!inputResult)
		{
			cout << "librarian code[10]: " << endl;
			inputResult = Input::readCode(librarian.code, 10, appCollections.librarians);
		}
		inputResult = false;

		while (!inputResult)
		{
			cout << "librarian name[50]: " << endl;
			inputResult = Input::readLine(librarian.name, 50);
		}

		inputResult = false;

		while (!inputResult)
		{
			cout << "librarian surname[50]: " << endl;
			inputResult = Input::readLine(librarian.surname, 50);
		}

		appCollections.librarians.push_back(librarian);

		return true;
	}
	);

	MenuCommand printLibrarians = MenuCommand("print Librarians", [&messageBus, &appCollections]() mutable
	{

		if (appCollections.librarians.size() == 0)
		{
			cout << "No librarians!" << endl;
			return true;
		}

		for (auto librarian : appCollections.librarians)
		{
			librarian.print();
			cout << endl;
		}

		return true;
	}
	);

	MenuCommand editLibrarian = MenuCommand("edit Librarian", [&messageBus, &appCollections]() mutable
	{
		int choice = -1;
		bool isInputCorrect = false;
		Librarian* librarian = NULL;

		const int BACK = 0;
		const int SET_LIBRARIAN_TO_EDIT = 1;
		const int EDIT_CODE = 2;
		const int EDIT_NAME = 3;
		const int EDIT_SURNAME = 4;
		

		do
		{
			if (librarian != NULL)
			{
				cout << "librarian to edit:" << endl;
				librarian->print();
				cout << endl;
			}

			cout << endl;
			cout << BACK << ": back" << endl;
			cout << SET_LIBRARIAN_TO_EDIT << ": set librarian to edit" << endl;
			cout << EDIT_CODE << ": edit code" << endl;
			cout << EDIT_NAME << ": edit name" << endl;
			cout << EDIT_SURNAME << ": edit surname" << endl;
			cout << endl;

			cout << "input choice: ";
			isInputCorrect = Input::readInt(choice);
			if (!isInputCorrect)
			{
				choice = -1;
			}

			if (choice == SET_LIBRARIAN_TO_EDIT)
			{
				char code[10];
				cout << "librarian code: ";
				bool inputResult = Input::readLine(code, 10);
				if (inputResult)
				{
					int index = findIndexByCode(appCollections.librarians, code);
					if (index == -1)
					{
						cout << "librarian not found" << endl;
						librarian = NULL;
					}
					else
					{
						librarian = &appCollections.librarians[index];
					}
				}
				else
				{
					cout << "bad input" << endl;
				}
			}
			else if (choice == EDIT_CODE)
			{
				if (librarian != NULL)
				{
					int charSize = size(librarian->code);
					char* newValue = new char[charSize]();
					char* oldValue = new char[charSize]();
					cout << "new code: ";
					bool inputResult = Input::readCode(newValue, charSize, appCollections.librarians);
					if (inputResult)
					{
						strcpy_s(oldValue, charSize, librarian->code);
						strcpy_s(librarian->code, charSize, newValue);

						for (auto bookReservation : appCollections.bookReservations)
						{
							if (strcmp(bookReservation.librarianCode, oldValue) == 0)
							{
								strcpy_s(bookReservation.librarianCode, charSize, newValue);
							}
						}
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no librarian set" << endl;
				}

			}
			else if (choice == EDIT_NAME)
			{
				if (librarian != NULL)
				{
					int charSize = size(librarian->name);
					char* newValue = new char[charSize]();
					cout << "new name: ";
					bool inputResult = Input::readLine(newValue, charSize);
					if (inputResult)
					{
						strcpy_s(librarian->name, charSize, newValue);
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no librarian set" << endl;
				}

			}
			else if (choice == EDIT_SURNAME)
			{
				if (librarian != NULL)
				{
					int charSize = size(librarian->surname);
					char* newValue = new char[charSize]();
					cout << "new surname: ";
					bool inputResult = Input::readLine(newValue, charSize);
					if (inputResult)
					{
						strcpy_s(librarian->surname, charSize, newValue);
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no librarian set" << endl;
				}
			}
		}
		while (choice != BACK);

		return true;
	}
	);

	librarianMenu.addMenuCommand(goToMainMenu);
	librarianMenu.addMenuCommand(addLibrarian);
	librarianMenu.addMenuCommand(printLibrarians);
	librarianMenu.addMenuCommand(editLibrarian);

	return librarianMenu;
}

Menu ReaderMenuFactory::makeReaderMenu(AppCollections &appCollections, MessageBus &messageBus, MenuCommand &goToMainMenu)
{
	Menu readerMenu = Menu(Menu::READER_MENU, "Reader Menu");

	MenuCommand addReader = MenuCommand("add reader", [&messageBus, &appCollections]() mutable
	{
		Reader reader;
		bool inputResult = false;

		while (!inputResult)
		{
			cout << "reader code[10]: " << endl;
			inputResult = Input::readCode(reader.code, 10, appCollections.readers);
		}
		inputResult = false;

		while (!inputResult)
		{
			cout << "reader name[50]: " << endl;
			inputResult = Input::readLine(reader.name, 50);
		}

		inputResult = false;

		while (!inputResult)
		{
			cout << "reader surname[50]: " << endl;
			inputResult = Input::readLine(reader.surname, 50);
		}

		appCollections.readers.push_back(reader);

		return true;
	}
	);

	MenuCommand printReaders = MenuCommand("print readers", [&messageBus, &appCollections]() mutable
	{

		if (appCollections.readers.size() == 0)
		{
			cout << "No readers!" << endl;
			return true;
		}

		for (auto reader : appCollections.readers)
		{
			reader.print();
			cout << endl;
		}

		return true;
	}
	);

	MenuCommand editReader = MenuCommand("edit reader", [&messageBus, &appCollections]() mutable
	{
		int choice = -1;
		bool isInputCorrect = false;
		Reader* reader = NULL;

		const int BACK = 0;
		const int SET_READER_TO_EDIT = 1;
		const int EDIT_CODE = 2;
		const int EDIT_NAME = 3;
		const int EDIT_SURNAME = 4;

		do
		{
			if (reader != NULL)
			{
				cout << "reader to edit:" << endl;
				reader->print();
				cout << endl;
			}

			cout << endl;
			cout << BACK << ": back" << endl;
			cout << SET_READER_TO_EDIT << ": set reader to edit" << endl;
			cout << EDIT_CODE << ": edit code" << endl;
			cout << EDIT_NAME << ": edit name" << endl;
			cout << EDIT_SURNAME << ": edit surname" << endl;
			cout << endl;

			cout << "input choice: ";
			isInputCorrect = Input::readInt(choice);
			if (!isInputCorrect)
			{
				choice = -1;
			}

			if (choice == SET_READER_TO_EDIT)
			{
				char code[10];
				cout << "reader code: ";
				bool inputResult = Input::readLine(code, 10);
				if (inputResult)
				{
					int index = findIndexByCode(appCollections.readers, code);
					if (index == -1)
					{
						cout << "reader not found" << endl;
						reader = NULL;
					}
					else
					{
						reader = &appCollections.readers[index];
					}
				}
				else
				{
					cout << "bad input" << endl;
				}
			}
			else if (choice == EDIT_CODE)
			{
				if (reader != NULL)
				{
					int charSize = size(reader->code);
					char* newValue = new char[charSize]();
					char* oldValue = new char[charSize]();
					cout << "new code: ";
					bool inputResult = Input::readCode(newValue, charSize, appCollections.readers);
					if (inputResult)
					{
						strcpy_s(oldValue, charSize, reader->code);
						strcpy_s(reader->code, charSize, newValue);

						for (auto bookReservation : appCollections.bookReservations)
						{
							if (strcmp(bookReservation.readerCode, oldValue) == 0)
							{
								strcpy_s(bookReservation.readerCode, charSize, newValue);
							}
						}
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no reader set" << endl;
				}
			}
			else if (choice == EDIT_NAME)
			{
				if (reader != NULL)
				{
					int charSize = size(reader->name);
					char* newValue = new char[charSize]();
					cout << "new name: ";
					bool inputResult = Input::readLine(newValue, charSize);
					if (inputResult)
					{
						strcpy_s(reader->name, charSize, newValue);
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no reader set" << endl;
				}
			}
			else if (choice == EDIT_SURNAME)
			{
				if (reader != NULL)
				{
					int charSize = size(reader->surname);
					char* newValue = new char[charSize]();
					cout << "new surname: ";
					bool inputResult = Input::readLine(newValue, charSize);
					if (inputResult)
					{
						strcpy_s(reader->surname, charSize, newValue);
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no reader set" << endl;
				}
			}
		}
		while (choice != BACK);

		return true;
	}
	);

	MenuCommand searchBookReservationsByReaderCode = MenuCommand("search books reservations by reader code", [&messageBus, &appCollections]() mutable
	{
		int choice = -1;
		bool isInputCorrect = false;
		bool isCodeFound = false;
		char searchCode[10] = "";

		const int BACK = 0;
		const int SET_CODE_TO_SEARCH = 1;
		const int PRINT_BOOK_RESERVATIONS = 2;
		const int DELETE_BOOK_RESERVATIONS = 3;

		do
		{
			cout << endl;
			cout << BACK << ": back" << endl;
			cout << SET_CODE_TO_SEARCH << ": set reader code" << endl;
			cout << PRINT_BOOK_RESERVATIONS << ": print book reservations" << endl;
			cout << DELETE_BOOK_RESERVATIONS << ": delete book reservations" << endl;
			cout << endl;

			cout << "input choice: ";
			isInputCorrect = Input::readInt(choice);
			if (!isInputCorrect)
			{
				choice = -1;
			}

			if (choice == SET_CODE_TO_SEARCH)
			{
				cout << "reader code: ";
				Input::readLine(searchCode, 10);
				int index = findIndexByCode(appCollections.readers, searchCode);
				if (index == -1)
				{
					isCodeFound = false;
					cout << "code not found" << endl;
				}
				else
				{
					isCodeFound = true;
					cout << "found book reservations: " << countBookReservationsByReaderCode(searchCode, appCollections.bookReservations) << endl << endl;
				}
			}
			else if (choice == PRINT_BOOK_RESERVATIONS)
			{
				if (isCodeFound)
				{
					cout << endl;
					printBookReservationsByReaderCode(searchCode, appCollections.bookReservations);
					cout << endl;
				}
				else
				{
					cout << "no code set" << endl;
				}
			}
			else if (choice == DELETE_BOOK_RESERVATIONS)
			{
				if (isCodeFound)
				{
					deleteBookReservationsByReaderCode(searchCode, appCollections.bookReservations);
					isCodeFound = false;
				}
				else
				{
					cout << "no code set" << endl;
				}
			}

		}
		while (choice != BACK);

		return true;
	}
	);

	MenuCommand printOrderedBySurname = MenuCommand("print ordered by surname", [&messageBus, &appCollections]() mutable
	{
		vector<Reader> orderedReaders = readersOrderedBySurname(appCollections.readers);

		if (orderedReaders.size() == 0)
		{
			cout << "no readers" << endl;
			cout << endl;
		}

		for (auto reader : orderedReaders)
		{
			reader.print();
			cout << endl;
		}

		return true;
	}
	);

	readerMenu.addMenuCommand(goToMainMenu);
	readerMenu.addMenuCommand(addReader);
	readerMenu.addMenuCommand(printReaders);
	readerMenu.addMenuCommand(editReader);
	readerMenu.addMenuCommand(searchBookReservationsByReaderCode);
	readerMenu.addMenuCommand(printOrderedBySurname);

	return readerMenu;
}

Menu bookReservationMenuFactory::makeBookReservationMenu(AppCollections &appCollections, MessageBus &messageBus, MenuCommand &goToMainMenu)
{
	Menu bookReservationMenu = Menu(Menu::BOOK_RESERVATION_MENU, "Book Reservation Menu");

	MenuCommand addBookReservation = MenuCommand("add book reservation", [&messageBus, &appCollections]() mutable
	{
		BookReservation bookReservation;
		bool inputResult = false;

		while (!inputResult)
		{
			cout << "book reservation code[10]: " << endl;
			inputResult = Input::readCode(bookReservation.code, 10, appCollections.bookReservations);
		}
		inputResult = false;

		while (!inputResult)
		{
			cout << "librarian code[10]: " << endl;
			char code[10];
			Input::readLine(code, 10);
			int index = findIndexByCode(appCollections.librarians, code);
			if (index == -1)
			{
				cout << "code not found" << endl;
				inputResult = false;
			}
			else
			{
				strcpy_s(bookReservation.librarianCode, code);
				inputResult = true;
			}
		}
		inputResult = false;

		while (!inputResult)
		{
			cout << "reader code[10]: " << endl;
			char code[10];
			Input::readLine(code, 10);
			int index = findIndexByCode(appCollections.readers, code);
			if (index == -1)
			{
				cout << "code not found" << endl;
				inputResult = false;
			}
			else
			{
				strcpy_s(bookReservation.readerCode, code);
				inputResult = true;
			}
		}
		inputResult = false;

		while (!inputResult)
		{
			cout << "book code[10]: " << endl;
			char code[10];
			Input::readLine(code, 10);
			int index = findIndexByCode(appCollections.books, code);
			if (index == -1)
			{
				cout << "code not found" << endl;
				inputResult = false;
			}
			else
			{
				strcpy_s(bookReservation.bookCode, code);
				inputResult = true;
			}
		}
		inputResult = false;

		while (!inputResult)
		{
			cout << "issue date: " << endl;
			cout << "Enter date in format 2019-02-25 :" << endl;
			inputResult = Input::readDate(bookReservation.issueDate);
		}
		inputResult = false;

		bookReservation.returnDate.year = 0;
		bookReservation.returnDate.month = 0;
		bookReservation.returnDate.day = 0;

		appCollections.bookReservations.push_back(bookReservation);

		return true;
	}
	);

	MenuCommand printBookReservations = MenuCommand("print book reservations", [&messageBus, &appCollections]() mutable
	{

		if (appCollections.bookReservations.size() == 0)
		{
			cout << "No book reservations!" << endl;
			return true;
		}

		for (auto bookReservation : appCollections.bookReservations)
		{
			bookReservation.print();
			cout << endl;
		}

		return true;
	}
	);

	MenuCommand editBookReservation = MenuCommand("edit book reservation", [&messageBus, &appCollections]() mutable
	{
		int choice = -1;
		bool isInputCorrect = false;
		BookReservation* bookReservation = NULL;

		const int BACK = 0;
		const int SET_BOOK_RESERVATION_TO_EDIT = 1;
		const int EDIT_CODE = 2;
		const int EDIT_LIBRARIAN_CODE = 3;
		const int EDIT_READER_CODE = 4;
		const int EDIT_BOOK_CODE = 5;
		const int EDIT_ISSUE_DATE = 6;
		const int EDIT_RETURN_DATE = 7;
		
		do
		{
			if (bookReservation != NULL)
			{
				cout << "book reservation to edit:" << endl;
				bookReservation->print();
				cout << endl;
			}

			cout << endl;
			cout << BACK << ": back" << endl;
			cout << SET_BOOK_RESERVATION_TO_EDIT << ": set book reservation to edit" << endl;
			cout << EDIT_CODE << ": edit code" << endl;
			cout << EDIT_LIBRARIAN_CODE << ": edit librarian code" << endl;
			cout << EDIT_READER_CODE << ": edit reader code" << endl;
			cout << EDIT_BOOK_CODE << ": edit book code" << endl;
			cout << EDIT_ISSUE_DATE << ": edit issue date" << endl;
			cout << EDIT_RETURN_DATE << ": edit return date" << endl;
			cout << endl;

			cout << "input choice: ";
			isInputCorrect = Input::readInt(choice);
			if (!isInputCorrect)
			{
				choice = -1;
			}

			if (choice == SET_BOOK_RESERVATION_TO_EDIT)
			{
				char code[10];
				cout << "book reservation code: ";
				bool inputResult = Input::readLine(code, 10);
				if (inputResult)
				{
					int index = findIndexByCode(appCollections.bookReservations, code);
					if (index == -1)
					{
						cout << "book reservation not found" << endl;
						bookReservation = NULL;
					}
					else
					{
						bookReservation = &appCollections.bookReservations[index];
					}
				}
				else
				{
					cout << "bad input" << endl;
				}
			}
			else if (choice == EDIT_CODE)
			{
				if (bookReservation != NULL)
				{
					int charSize = size(bookReservation->code);
					char* newValue = new char[charSize]();
					cout << "new code: ";
					bool inputResult = Input::readCode(newValue, charSize, appCollections.bookReservations);
					if (inputResult)
					{
						strcpy_s(bookReservation->code, charSize, newValue);
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no book reservation set" << endl;
				}
			}
			else if (choice == EDIT_LIBRARIAN_CODE)
			{
				if (bookReservation != NULL)
				{
					cout << "librarian code[10]: " << endl;
					int charSize = size(bookReservation->librarianCode);
					char* newValue = new char[charSize]();
					Input::readLine(newValue, charSize);
					int index = findIndexByCode(appCollections.librarians, newValue);
					if (index == -1)
					{
						cout << "code not found" << endl;
					}
					else
					{
						strcpy_s(bookReservation->librarianCode, charSize, newValue);
						cout << "updated" << endl;
					}
				}
				else
				{
					cout << "no book reservation set" << endl;
				}
			}
			else if (choice == EDIT_READER_CODE)
			{
				if (bookReservation != NULL)
				{
					cout << "reader code[10]: " << endl;
					int charSize = size(bookReservation->readerCode);
					char* newValue = new char[charSize]();
					Input::readLine(newValue, charSize);
					int index = findIndexByCode(appCollections.readers, newValue);
					if (index == -1)
					{
						cout << "code not found" << endl;
					}
					else
					{
						strcpy_s(bookReservation->readerCode, charSize, newValue);
						cout << "updated" << endl;
					}
				}
				else
				{
					cout << "no book reservation set" << endl;
				}
			}
			else if (choice == EDIT_BOOK_CODE)
			{
				if (bookReservation != NULL)
				{
					cout << "book code[10]: " << endl;
					int charSize = size(bookReservation->bookCode);
					char* newValue = new char[charSize]();
					Input::readLine(newValue, charSize);
					int index = findIndexByCode(appCollections.books, newValue);
					if (index == -1)
					{
						cout << "code not found" << endl;
					}
					else
					{
						strcpy_s(bookReservation->bookCode, charSize, newValue);
						cout << "updated" << endl;
					}
				}
				else
				{
					cout << "no book reservation set" << endl;
				}
			}
			else if (choice == EDIT_ISSUE_DATE)
			{
				if (bookReservation != NULL)
				{
					bool inputResult = false;
					cout << "issue date: " << endl;
					cout << "Enter date in format 2019-02-25 :" << endl;
					Date newValue = Date();
					inputResult = Input::readDate(newValue);
					if (inputResult)
					{
						bookReservation->issueDate = newValue;
						cout << "updated" << endl;
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no book reservation set" << endl;
				}
			}
			else if (choice == EDIT_RETURN_DATE)
			{
				if (bookReservation != NULL)
				{
					bool inputResult = false;
					cout << "return date: " << endl;
					cout << "Enter date in format 2019-02-25 :" << endl;
					Date newValue = Date();
					inputResult = Input::readDate(newValue);
					if (inputResult)
					{
						if (Date::cmp(newValue, bookReservation->issueDate) == -1)
						{
							cout << "return date can not be smaller than issue date" << endl;
						}
						else
						{
							bookReservation->returnDate = newValue;
							cout << "updated" << endl;
						}
					}
					else
					{
						cout << "bad input" << endl;
					}
				}
				else
				{
					cout << "no book reservation set" << endl;
				}
			}
		}
		while (choice != BACK);

		return true;
	}
	);

	MenuCommand deleteBookReservation = MenuCommand("delete book reservation", [&messageBus, &appCollections]() mutable
	{
		
		cout << "book reservation code: ";
		char code[10];
		bool inputResult = Input::readLine(code, 10);

		if (inputResult)
		{
			if (containsCode(appCollections.bookReservations, code))
			{
				deleteByCode(appCollections.bookReservations, code);
				cout << "deleted" << endl;
			}
			else
			{
				cout << "code not found" << endl;
			}
		}
		else
		{
			cout << "bad input" << endl;
		}

		cout << endl;

		return true;
	}
	);

	MenuCommand printOrderedByIssueDate = MenuCommand("print ordered by issue date", [&messageBus, &appCollections]() mutable
	{
		vector<BookReservation> orderedReservations = bookReservationsOrderedByIssueDate(appCollections.bookReservations);
		for (auto bookReservation : orderedReservations)
		{
			bookReservation.print();
			cout << endl;
		}

		return true;
	}
	);

	MenuCommand findByIssueDate = MenuCommand("find by issue date", [&messageBus, &appCollections]() mutable
	{
		bool inputResult = false;
		cout << "issue date: " << endl;
		cout << "Enter date in format 2019-02-25 :" << endl;
		Date date;
		inputResult = Input::readDate(date);
		if (inputResult)
		{
			vector<BookReservation> results = findBookReservationsByIssueDate(appCollections.bookReservations, date);
			if (results.size() == 0)
			{
				cout << "no results found" << endl;
			}
			else
			{
				cout << endl;
				for (auto bookReservation : results)
				{
					bookReservation.print();
					cout << endl;
				}
			}
		}
		else
		{
			cout << "bad input" << endl;
		}

		cout << endl;

		return true;
	}
	);

	MenuCommand bookReservationsPerReader = MenuCommand("book reservations per reader", [&messageBus, &appCollections]() mutable
	{
		cout << endl;
		printBookReservationsPerReader(appCollections.bookReservations, appCollections.readers);
		cout << endl;

		return true;
	}
	);

	MenuCommand readerAvgBookReservations = MenuCommand("reader avg book reservations", [&messageBus, &appCollections]() mutable
	{
		cout << endl;
		printReaderAvgBookReservations(appCollections.bookReservations, appCollections.readers);
		cout << endl;

		return true;
	}
	);

	MenuCommand uniqueReservedBooksPerYear = MenuCommand("unique reserved books per year", [&messageBus, &appCollections]() mutable
	{
		cout << endl;
		printUniqueReservedBooksPerYear(appCollections.books, appCollections.bookReservations);
		cout << endl;

		return true;
	}
	);

	bookReservationMenu.addMenuCommand(goToMainMenu);
	bookReservationMenu.addMenuCommand(addBookReservation);
	bookReservationMenu.addMenuCommand(printBookReservations);
	bookReservationMenu.addMenuCommand(editBookReservation);
	bookReservationMenu.addMenuCommand(deleteBookReservation);
	bookReservationMenu.addMenuCommand(printOrderedByIssueDate);
	bookReservationMenu.addMenuCommand(findByIssueDate);
	bookReservationMenu.addMenuCommand(bookReservationsPerReader);
	bookReservationMenu.addMenuCommand(readerAvgBookReservations);
	bookReservationMenu.addMenuCommand(uniqueReservedBooksPerYear);

	return bookReservationMenu;
}
