#pragma once

#include <string>

using namespace std;

struct Date
{
public:
	int year;
	int month;
	int day;

	void print();
	static int cmpYear(const Date& date1, const Date& date2);
	static int cmpMonth(const Date& date1, const Date& date2);
	static int cmpDay(const Date& date1, const Date& date2);
	static int cmp(const Date& date1, const Date& date2);
};

enum Month
{
	Jan = 1, Feb = 2, Mar = 3, Apr = 4, May = 5, Jun = 6, Jul = 7,
	Aug = 8, Sep = 9, Oct = 10, Nov = 11, Dec = 12
};

string getMonthName(const int month);
bool hasOnlyDigits(const string& input);
bool isLeapYear(const int year);
bool isValidDay(const int day, const int month, const int year);
