
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

static class Input
{
public:
	static bool readLine(char *cstring, const int size)
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

	static bool readInt(int &integer)
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

	static bool getDateTime(tm &tm)
	{
		cout << "Please, enter the time: ";
		cin >> get_time(&tm, "%Y-%m-%d");

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return false;
		}

		return true;
	}
};
