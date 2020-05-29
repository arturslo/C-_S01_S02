#include "Input.h"

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

bool Input::readLine(char *cstring, const int size)
{
	cin.getline(cstring, size);
	if (cin.fail())
	{
		cstring[0] = '\0';
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}

	return true;
}

bool Input::readInt(int &integer)
{
	long limit = numeric_limits<int>::max();
	int limitLength = to_string(limit).length() + 1;
	char *intCString = new char[limitLength];

	bool readResult = readLine(intCString, limitLength);
	if (!readResult)
	{
		integer = 0;
		return false;
	}

	if (intCString[0] == '\0')
	{
		return false;
	}

	bool isStringNumeric = true;
	int inputLength = strlen(intCString);
	for (int i = 0; i < inputLength; i++)
	{
		if (!isdigit(intCString[i]))
		{
			isStringNumeric = false;
			break;
		}
	}

	if (!isStringNumeric)
	{
		integer = 0;
		return false;
	}

	integer = atoi(intCString);
	return true;
}

bool Input::readDate(Date &date)
{
	const char SEPERATOR = '-';
	string dateInput = "";
	string part1 = "";
	string part2 = "";
	string part3 = "";
	size_t pos1 = string::npos;
	size_t pos2 = string::npos;
	int yearInt = 0;
	int monthInt = 0;
	int dayInt = 0;
	
	getline(cin, dateInput);

	pos1 = dateInput.find(SEPERATOR);
	pos2 = dateInput.find(SEPERATOR, pos1 + 1);

	if (pos1 == string::npos || pos2 == string::npos)
	{
		return false;
	}

	part1 = dateInput.substr(0, pos1);
	part2 = dateInput.substr(pos1 + 1, pos2 - pos1 - 1);
	part3 = dateInput.substr(pos2 + 1);

	if (part1.length() != 4 || part2.length() != 2 || part3.length() != 2)
	{
		return false;
	}

	if (!hasOnlyDigits(part1) || !hasOnlyDigits(part2) || !hasOnlyDigits(part3))
	{
		return false;
	}

	yearInt = stoi(part1);
	monthInt = stoi(part2);
	dayInt = stoi(part3);
	
	if (monthInt < 1 || monthInt > 12)
	{
		return false;
	}

	if (!isValidDay(dayInt, monthInt, yearInt))
	{
		return false;
	}

	date.year = yearInt;
	date.month = monthInt;
	date.day = dayInt;

	return true;
}
