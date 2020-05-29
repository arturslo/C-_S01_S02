#include "AppCollections.h"

AppCollections::AppCollections(const vector<Book> &books, const vector<Librarian> &librarians, const vector<Reader> &readers, const vector<BookReservation> &bookReservations)
{
	this->books = books;
	this->librarians = librarians;
	this->readers = readers;
	this->bookReservations = bookReservations;
}
