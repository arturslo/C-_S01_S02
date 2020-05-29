#define _CRT_SECURE_NO_WARNINGS

#include "DataStructures.h"
#include "Date.h"

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void Book::print()
{
	printChar(OBJ_SEPERATOR_CHAR, OBJ_SEPERATOR_TIMES);
	cout << setw(VAR_NAME_WIDTH) << "code: " << code << endl;
	cout << setw(VAR_NAME_WIDTH) << "title: " << title << endl;
	cout << setw(VAR_NAME_WIDTH) << "author: " << author << endl;
	cout << setw(VAR_NAME_WIDTH) << "yearOfIssue: " << yearOfIssue << endl;
	cout << setw(VAR_NAME_WIDTH) << "genre: " << genre << endl;
}

void Person::print()
{
	printChar(OBJ_SEPERATOR_CHAR, OBJ_SEPERATOR_TIMES);
	cout << setw(VAR_NAME_WIDTH) << "code: " << code << endl;
	cout << setw(VAR_NAME_WIDTH) << "name: " << name << endl;
	cout << setw(VAR_NAME_WIDTH) << "surname: " << surname << endl;
}

void BookReservation::print()
{
	printChar(OBJ_SEPERATOR_CHAR, OBJ_SEPERATOR_TIMES);
	cout << setw(VAR_NAME_WIDTH) << "code: " << code << endl;
	cout << setw(VAR_NAME_WIDTH) << "librarian code: " << librarianCode << endl;
	cout << setw(VAR_NAME_WIDTH) << "reader code: " << readerCode << endl;
	cout << setw(VAR_NAME_WIDTH) << "book code: " << bookCode << endl;
	cout << endl;
	cout << setw(VAR_NAME_WIDTH) << "issue date: " << endl;
	issueDate.print();
	cout << endl;
	cout << setw(VAR_NAME_WIDTH) << "return date: " << endl;
	returnDate.print();
	cout << endl;
}

void printChar(const char c, const int times)
{
	for (int i = 0; i < times; i++)
	{
		cout << c;
	}
	cout << endl;
}

void printBooksByYear(const int year, const vector<Book>& books)
{
	for (auto book : books)
	{
		if (book.yearOfIssue == year)
		{
			book.print();
			cout << endl;
		}
	}
}

int countBooksByYear(const int year, const vector<Book>& books)
{
	int count = 0;
	for (auto book : books)
	{
		if (book.yearOfIssue == year)
		{
			count++;
		}
	}

	return count;
}

void deleteBooksByYear(const int year, vector<Book>& books, vector<BookReservation>& bookReservations)
{
	vector<Book>::iterator it = books.begin();
	while (it != books.end())
	{
		if ((*it).yearOfIssue == year)
		{
			deleteBookReservationsByBookCode((*it).code, bookReservations);
			it = books.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void deleteBookReservationsByBookCode(const char* code, vector<BookReservation>& bookReservations)
{
	vector<BookReservation>::iterator it = bookReservations.begin();
	while (it != bookReservations.end())
	{
		if (strcmp((*it).bookCode, code) == 0)
		{
			it = bookReservations.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void printBookReservationsByReaderCode(const char* code, const vector<BookReservation>& bookReservations)
{
	for (auto bookReservation : bookReservations)
	{
		if (strcmp(bookReservation.readerCode, code) == 0)
		{
			bookReservation.print();
			cout << endl;
		}
	}
}

void deleteBookReservationsByReaderCode(const char* code, vector<BookReservation>& bookReservations)
{
	vector<BookReservation>::iterator it = bookReservations.begin();
	while (it != bookReservations.end())
	{
		if (strcmp((*it).readerCode, code) == 0)
		{
			it = bookReservations.erase(it);
		}
		else
		{
			it++;
		}
	}
}

int countBookReservationsByReaderCode(const char* code, const vector<BookReservation>& bookReservations)
{
	int count = 0;
	for (auto bookReservation : bookReservations)
	{
		if (strcmp(bookReservation.readerCode, code) == 0)
		{
			count++;
		}
	}

	return count;
}

vector<BookReservation> bookReservationsOrderedByIssueDate(vector<BookReservation> items)
{
	bool doSwap = true;
	BookReservation tmp;
	while (doSwap)
	{
		doSwap = false;
		for (size_t i = 0; i < items.size() - 1; i++)
		{
			if (Date::cmp(items[i].issueDate, items[i + 1].issueDate) == -1)
			{
				tmp = items[i];
				items[i] = items[i + 1];
				items[i + 1] = tmp;
				doSwap = true;
			}
		}
	}

	return items;
}

vector<BookReservation> findBookReservationsByIssueDate(const vector<BookReservation>& bookReservations, const Date& date)
{
	vector<BookReservation> result;

	for (auto bookReservation : bookReservations)
	{
		if (Date::cmp(bookReservation.issueDate, date) == 0)
		{
			result.push_back(bookReservation);
		}
	}

	return result;
}

int strCmp(const char* cstring1, const char* cstring2)
{
	int length1 = strlen(cstring1);
	int length2 = strlen(cstring2);
	int res = 0;
	int char1 = 0;
	int char2 = 0;
	int tmp;

	if (length2 > length1)
	{
		return -strCmp(cstring2, cstring1);
	}

	for (int i = 0; i < length1; i++)
	{
		char1 = (int)cstring1[i];
		if (i > length2 - 1)
		{
			char2 = 0;
		}
		else
		{
			char2 = (int)cstring2[i];
		}
		tmp = char1 - char2;
		if (tmp != 0)
		{
			res = tmp;
			break;
		}
	}

	return res;
}

vector<Reader> readersOrderedBySurname(vector<Reader> items)
{
	bool doSwap = true;
	Reader tmp;
	while (doSwap)
	{
		doSwap = false;
		for (size_t i = 0; i < items.size() - 1; i++)
		{
			if (strCmp(items[i].surname, items[i + 1].surname) > 0)
			{
				tmp = items[i];
				items[i] = items[i + 1];
				items[i + 1] = tmp;
				doSwap = true;
			}
		}
	}

	return items;
}

vector<Book> booksOrderedByIssueYear(vector<Book> items)
{
	bool doSwap = true;
	Book tmp;
	while (doSwap)
	{
		doSwap = false;
		for (size_t i = 0; i < items.size() - 1; i++)
		{
			if (items[i].yearOfIssue > items[i + 1].yearOfIssue)
			{
				tmp = items[i];
				items[i] = items[i + 1];
				items[i + 1] = tmp;
				doSwap = true;
			}
		}
	}

	return items;
}

void printBookReservationsPerReader(const vector<BookReservation>& bookReservations, const vector<Reader>& readers)
{
	for (auto reader : readers)
	{
		cout << "reader code: " << setw(10) << reader.code << "  count: ";
		cout << countBookReservationsByReaderCode(reader.code, bookReservations);
		cout << endl;
	}
}

void printReaderAvgBookReservations(const vector<BookReservation>& bookReservations, const vector<Reader>& readers)
{
	int reservationCount = bookReservations.size();
	int readerCount = readers.size();
	float mean = ((float)reservationCount / (float)readerCount) * 100;
	cout << "avg: " << mean << endl;
}

vector<BooksInYear> getBooksPerYear(const vector<Book>& books)
{
	vector<BooksInYear> booksPerYear;
	bool yearFound = false;
	for (auto book : books)
	{
		for (auto& booksInYear : booksPerYear)
		{
			if (booksInYear.year == book.yearOfIssue)
			{
				booksInYear.books.push_back(book);
				yearFound = true;
				break;
			}
		}

		if (!yearFound)
		{
			BooksInYear newBooksInYear;
			newBooksInYear.year = book.yearOfIssue;
			newBooksInYear.books.push_back(book);
			booksPerYear.push_back(newBooksInYear);
		}
	}

	return booksPerYear;
}

bool hasBookBeenReserved(const Book& book, const vector<BookReservation>& bookReservations)
{
	bool hasBeenReserved = false;
	for (auto bookReservation : bookReservations)
	{
		if (strCmp(bookReservation.bookCode, book.code) == 0)
		{
			hasBeenReserved = true;
			break;
		}
	}

	return hasBeenReserved;
}

void printUniqueReservedBooksPerYear(const vector<Book>& books, const vector<BookReservation>& bookReservations)
{
	int reservedBooksInYear = 0;
	int countBooksInYear = 0;
	float percent = 0.00;
	vector<BooksInYear> booksPerYear = getBooksPerYear(books);
	for (auto booksInYear : booksPerYear)
	{
		reservedBooksInYear = 0;
		for (auto book : booksInYear.books)
		{
			if (hasBookBeenReserved(book, bookReservations))
			{
				reservedBooksInYear++;
			}
		}

		countBooksInYear = booksInYear.books.size();
		percent = ((float)reservedBooksInYear / (float)countBooksInYear) * 100;
		cout << "year: " << left << setw(4) << booksInYear.year << " books in year: " << left << setw(6) << countBooksInYear;
		cout << " reserved: " << left << setw(6) << reservedBooksInYear << "percent: " << left << setw(6) << percent << endl;
	}
}
