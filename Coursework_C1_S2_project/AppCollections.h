#pragma once

#include <vector>
#include "DataStructures.h"

class AppCollections
{
public:
	vector<Book> books;
	vector<Librarian> librarians;
	vector<Reader> readers;
	vector<BookReservation> bookReservations;

	AppCollections(const vector<Book> &books, const vector<Librarian> &librarians, const vector<Reader> &readers, const vector<BookReservation> &bookReservations);
};
