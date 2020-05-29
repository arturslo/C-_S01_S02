#pragma once

#include <vector>
#include <iostream>
#include "Date.h"

using namespace std;

class Input
{
public:
	static bool readLine(char *cstring, const int size);
	static bool readInt(int &integer);
	static bool readDate(Date &date);
	template <class T>
	static bool readCode(char *cstring, const int size, vector<T> items)
	{
		bool inputResult = Input::readLine(cstring, size);
		if (inputResult)
		{
			if (containsCode(items, cstring))
			{
				cout << "Code already in use" << endl;
				inputResult = false;
			}
		}

		return inputResult;
	}
};
