#include <string>
#include <iostream>
#include <iomanip>

#include "Date.h"
#include "DataStructures.h"

using namespace std;

string getMonthName(const int month)
{
	switch (month)
	{
	case 0:
		return "Not set";
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	default:
		return "Invalid month";
	}
}

bool hasOnlyDigits(const string& input)
{
	for (char c : input)
	{
		if (!isdigit(c))
		{
			return false;
		}
	}

	return true;
}

bool isLeapYear(const int year)
{
	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isValidDay(const int day, const int month, const int year)
{
	int days30[] = { 4, 6, 9, 11 };
	int days31[] = { 1, 3, 5, 7, 8, 10, 12 };

	int *monthFind = std::find(std::begin(days30), std::end(days30), month);

	if (monthFind != std::end(days30))
	{
		if (day >= 1 && day <= 30)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	monthFind = std::find(std::begin(days31), std::end(days31), month);

	if (monthFind != std::end(days31))
	{
		if (day >= 1 && day <= 31)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (month == 2)
	{
		int maxDays = 28;
		if (isLeapYear(year))
		{
			maxDays = 29;
		}

		if (day >= 1 && day <= maxDays)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

void Date::print()
{
	string stringYear = (year == 0) ? "Not set" : to_string(year);
	cout << setw(VAR_NAME_WIDTH) << "year: " << stringYear << endl;
	cout << setw(VAR_NAME_WIDTH) << "month: " << getMonthName(month) << endl;
	string stringDay = (day == 0) ? "Not set" : to_string(day);
	cout << setw(VAR_NAME_WIDTH) << "day: " << stringDay << endl;
}

int Date::cmp(const Date& date1, const Date& date2)
{
	int yearCmp = Date::cmpYear(date1, date2);
	int monthCmp = Date::cmpMonth(date1, date2);
	int dayCmp = Date::cmpDay(date1, date2);

	if (yearCmp == -1)
	{
		return -1;
	}
	else if (yearCmp == 0 && monthCmp == -1)
	{
		return -1;
	}
	else if (yearCmp == 0 && monthCmp == 0 && dayCmp == -1)
	{
		return -1;
	}
	else if (yearCmp == 0 && monthCmp == 0 && dayCmp == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int Date::cmpYear(const Date& date1, const Date& date2)
{
	if (date1.year < date2.year)
	{
		return -1;
	}
	else if (date1.year > date2.year)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Date::cmpMonth(const Date& date1, const Date& date2)
{
	if (date1.month < date2.month)
	{
		return -1;
	}
	else if (date1.month > date2.month)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Date::cmpDay(const Date& date1, const Date& date2)
{
	if (date1.day < date2.day)
	{
		return -1;
	}
	else if (date1.day > date2.day)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
