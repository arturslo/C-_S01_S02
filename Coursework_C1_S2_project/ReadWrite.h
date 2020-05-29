#pragma once

#include <vector>
#include "DataStructures.h"

using namespace std;

template <class T>
bool writeToFile(vector<T> &vector);
template <class T>
bool readFromFile(vector<T> &vector);

bool writeToFile(vector<Book> &vector);
bool readFromFile(vector<Book> &vector);
bool writeToFile(vector<Librarian> &vector);
bool readFromFile(vector<Librarian> &vector);
bool writeToFile(vector<Reader> &vector);
bool readFromFile(vector<Reader> &vector);
bool writeToFile(vector<BookReservation> &vector);
bool readFromFile(vector<BookReservation> &vector);
