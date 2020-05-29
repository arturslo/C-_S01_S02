#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "DataStructures.h"
#include "ReadWrite.h"

using namespace std;

bool readFromFile(vector<Book> &vector)
{
	ifstream infile;
	infile.open("books.txt", ios::in);

	if (!infile)
	{
		cout << "File open for reading failed" << endl;
		infile.close();
		return false;
	}

	string line;

	while (infile.good())
	{
		Book book;

		getline(infile, line);

		if (line.length() == 0)
		{
			break;
		}

		strcpy_s(book.code, line.c_str());
		getline(infile, line);
		strcpy_s(book.title, line.c_str());
		getline(infile, line);
		strcpy_s(book.author, line.c_str());

		getline(infile, line);
		book.yearOfIssue = stoi(line);

		getline(infile, line);
		strcpy_s(book.genre, line.c_str());

		if (infile.fail())
		{
			cout << "File read error" << endl;
			infile.close();
			return false;
		}
		vector.push_back(book);
	}

	infile.close();
	return true;
}

bool writeToFile(vector<Book> &vector)
{
	ofstream outfile;
	outfile.open("books.txt", ios::out | ios::trunc);
	if (!outfile)
	{
		cout << "File open for writing failed" << endl;
		outfile.close();
		return false;
	}

	for (Book book : vector)
	{
		outfile << book.code << endl;
		outfile << book.title << endl;
		outfile << book.author << endl;
		outfile << book.yearOfIssue << endl;
		outfile << book.genre << endl;

		if (outfile.fail())
		{
			cout << "File write error" << endl;
			outfile.close();
			return false;
		}
	}

	outfile.close();
	return true;
}

bool readFromFile(vector<Librarian> &vector)
{
	ifstream infile;
	infile.open("librarians.txt", ios::in);

	if (!infile)
	{
		cout << "File open for reading failed" << endl;
		infile.close();
		return false;
	}

	string line;

	while (infile.good())
	{
		Librarian librarian;

		getline(infile, line);

		if (line.length() == 0)
		{
			break;
		}

		strcpy_s(librarian.code, line.c_str());
		getline(infile, line);
		strcpy_s(librarian.name, line.c_str());
		getline(infile, line);
		strcpy_s(librarian.surname, line.c_str());

		if (infile.fail())
		{
			cout << "File read error" << endl;
			infile.close();
			return false;
		}
		vector.push_back(librarian);
	}

	infile.close();
	return true;
}

bool writeToFile(vector<Librarian> &vector)
{
	ofstream outfile;
	outfile.open("librarians.txt", ios::out | ios::trunc);
	if (!outfile)
	{
		cout << "File open for writing failed" << endl;
		outfile.close();
		return false;
	}

	for (Librarian librarian : vector)
	{
		outfile << librarian.code << endl;
		outfile << librarian.name << endl;
		outfile << librarian.surname << endl;

		if (outfile.fail())
		{
			cout << "File write error" << endl;
			outfile.close();
			return false;
		}
	}

	outfile.close();
	return true;
}

bool readFromFile(vector<Reader> &vector)
{
	ifstream infile;
	infile.open("readers.txt", ios::in);

	if (!infile)
	{
		cout << "File open for reading failed" << endl;
		infile.close();
		return false;
	}

	string line;

	while (infile.good())
	{
		Reader reader;

		getline(infile, line);

		if (line.length() == 0)
		{
			break;
		}

		strcpy_s(reader.code, line.c_str());
		getline(infile, line);
		strcpy_s(reader.name, line.c_str());
		getline(infile, line);
		strcpy_s(reader.surname, line.c_str());

		if (infile.fail())
		{
			cout << "File read error" << endl;
			infile.close();
			return false;
		}
		vector.push_back(reader);
	}

	infile.close();
	return true;
}

bool writeToFile(vector<Reader> &vector)
{
	ofstream outfile;
	outfile.open("readers.txt", ios::out | ios::trunc);
	if (!outfile)
	{
		cout << "File open for writing failed" << endl;
		outfile.close();
		return false;
	}

	for (Reader reader : vector)
	{
		outfile << reader.code << endl;
		outfile << reader.name << endl;
		outfile << reader.surname << endl;

		if (outfile.fail())
		{
			cout << "File write error" << endl;
			outfile.close();
			return false;
		}
	}

	outfile.close();
	return true;
}

bool readFromFile(vector<BookReservation> &vector)
{
	ifstream infile;
	infile.open("book_reservations.txt", ios::in);

	if (!infile)
	{
		cout << "File open for reading failed" << endl;
		infile.close();
		return false;
	}

	string line;

	while (infile.good())
	{
		BookReservation bookReservation;

		getline(infile, line);

		if (line.length() == 0)
		{
			break;
		}

		strcpy_s(bookReservation.code, line.c_str());
		getline(infile, line);
		strcpy_s(bookReservation.librarianCode, line.c_str());
		getline(infile, line);
		strcpy_s(bookReservation.readerCode, line.c_str());
		getline(infile, line);
		strcpy_s(bookReservation.bookCode, line.c_str());

		getline(infile, line);
		bookReservation.issueDate.year = stoi(line);
		getline(infile, line);
		bookReservation.issueDate.month = stoi(line);
		getline(infile, line);
		bookReservation.issueDate.day = stoi(line);

		getline(infile, line);
		bookReservation.returnDate.year = stoi(line);
		getline(infile, line);
		bookReservation.returnDate.month = stoi(line);
		getline(infile, line);
		bookReservation.returnDate.day = stoi(line);

		if (infile.fail())
		{
			cout << "File read error" << endl;
			infile.close();
			return false;
		}
		vector.push_back(bookReservation);
	}

	infile.close();
	return true;
}

bool writeToFile(vector<BookReservation> &vector)
{
	ofstream outfile;
	outfile.open("book_reservations.txt", ios::out | ios::trunc);
	if (!outfile)
	{
		cout << "File open for writing failed" << endl;
		outfile.close();
		return false;
	}

	for (BookReservation bookReservation : vector)
	{
		outfile << bookReservation.code << endl;
		outfile << bookReservation.librarianCode << endl;
		outfile << bookReservation.readerCode << endl;
		outfile << bookReservation.bookCode << endl;

		outfile << bookReservation.issueDate.year << endl;
		outfile << bookReservation.issueDate.month << endl;
		outfile << bookReservation.issueDate.day << endl;

		outfile << bookReservation.returnDate.year << endl;
		outfile << bookReservation.returnDate.month << endl;
		outfile << bookReservation.returnDate.day << endl;

		if (outfile.fail())
		{
			cout << "File write error" << endl;
			outfile.close();
			return false;
		}
	}

	outfile.close();
	return true;
}
