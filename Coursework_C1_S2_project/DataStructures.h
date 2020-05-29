#pragma once

#include <ctime>
#include <vector>

#include "Date.h"

using namespace std;

const int VAR_NAME_WIDTH = 18;
const char OBJ_SEPERATOR_CHAR = '-';
const int OBJ_SEPERATOR_TIMES = 50;

struct Book
{
public:
	char code[10];
	char title[50];
	char author[50];
	int yearOfIssue;
	char genre[20];

	void print();
};

struct Person
{
	char code[10];
	char name[50];
	char surname[50];

	void print();
};

struct Librarian : Person
{
};

struct Reader : Person
{
};

struct BookReservation
{
	char code[10];
	char librarianCode[10];
	char readerCode[10];
	char bookCode[10];
	Date issueDate;
	Date returnDate;

	void print();
};

void printChar(const char c, const int times);

template <class T>
bool containsCode(vector<T> items, char* code)
{
	bool codeIsFound = false;

	for (auto item : items)
	{
		if (strcmp(item.code, code) == 0)
		{
			codeIsFound = true;
			break;
		}
	}

	return codeIsFound;
}

template <class T>
int findIndexByCode(vector<T> items, char* code)
{
	for (vector<int>::size_type i = 0; i != items.size(); i++)
	{
		if (strcmp(items[i].code, code) == 0)
		{
			return i;
		}
	}

	return -1;
}

template <class T>
void deleteByCode(vector<T>& items, char* code)
{
	typename vector<T>::iterator it = items.begin();
	while (it != items.end())
	{
		if (strcmp((*it).code, code) == 0)
		{
			it = items.erase(it);
		}
		else
		{
			it++;
		}
	}
}

struct BooksInYear
{
	int year;
	vector<Book> books;
};

void printBooksByYear(const int year, const vector<Book>& books);
int countBooksByYear(const int year, const vector<Book>& books);
void deleteBooksByYear(const int year, vector<Book>& books, vector<BookReservation>& bookReservations);
vector<Book> booksOrderedByIssueYear(vector<Book> books);

void deleteBookReservationsByBookCode(const char* code, vector<BookReservation>& bookReservations);
void printBookReservationsByReaderCode(const char* code, const vector<BookReservation>& bookReservations);
void deleteBookReservationsByReaderCode(const char* code, vector<BookReservation>& bookReservations);
int countBookReservationsByReaderCode(const char* code, const vector<BookReservation>& bookReservations);
vector<BookReservation> bookReservationsOrderedByIssueDate(vector<BookReservation> bookReservations);
vector<BookReservation> findBookReservationsByIssueDate(const vector<BookReservation>& bookReservations, const Date& date);

int strCmp(const char* cstring1, const char* cstring2);
vector<Reader> readersOrderedBySurname(vector<Reader> readers);

void printBookReservationsPerReader(const vector<BookReservation>& bookReservations, const vector<Reader>& readers);
void printReaderAvgBookReservations(const vector<BookReservation>& bookReservations, const vector<Reader>& readers);

vector<BooksInYear> getBooksPerYear(const vector<Book>& books);
bool hasBookBeenReserved(const Book& book, const vector<BookReservation>& bookReservations);
void printUniqueReservedBooksPerYear(const vector<Book>& books, const vector<BookReservation>& bookReservations);
