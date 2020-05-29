#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	int rowCount;
	int columnCount;

	cout << "Input row count <int> : ";
	cin >> rowCount;
	cout << "Input column count <int> : ";
	cin >> columnCount;
	cout << endl;

	if (rowCount < 0) {
		cout << "Row count cannot be less than 0";
		return 1;
	}

	if (columnCount < 0) {
		cout << "Coulumn count cannot be less than 0";
		return 1;
	}

	int **rows = new int *[rowCount];

	for (int i = 0; i < rowCount; i++) {
		rows[i] = new int[columnCount];
	}

	int generationType;
	const int MANUAL_GENERATION = 1;
	const int AUTOMATIC_GENERATION = 2;

	cout << "Array generation types:" << endl;
	cout << "1) Manual generation" << endl;
	cout << "2) Automatic generation" << endl << endl;

	cout << "Input array generation type: ";
	cin >> generationType;
	cout << endl;

	if (generationType != MANUAL_GENERATION && generationType != AUTOMATIC_GENERATION) {
		cout << "No such generation type" << endl;
		return 1;
	}

	if (generationType == MANUAL_GENERATION) {
		for (int index1 = 0; index1 < rowCount; index1++) {
			for (int index2 = 0; index2 < columnCount; index2++) {
				cout << "Input element [" << index1 << "][" << index2 << "]: ";
				cin >> rows[index1][index2];
			}
		}
	}

	if (generationType == AUTOMATIC_GENERATION) {

		int rangeStart;
		int rangeEnd;

		cout << "Input range start: ";
		cin >> rangeStart;
		cout << "Input range end: ";
		cin >> rangeEnd;
		cout << endl;

		if (rangeStart > rangeEnd) {
			cout << "Range start cannot be lareger than range end" << endl;
			return 1;
		}

		cout << "Numbers will be generated in range [" << rangeStart << ":" << rangeEnd << "]" << endl << endl;

		srand(time(NULL));
		int random;
		for (int index1 = 0; index1 < rowCount; index1++) {
			for (int index2 = 0; index2 < columnCount; index2++) {
				random = rangeStart + rand() % (rangeEnd - rangeStart + 1);
				rows[index1][index2] = random;
			}
		}
	}

	cout << "Current array: " << endl << endl;
	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
		for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
			cout << rows[rowIndex][columnIndex] << " ";
		}
		cout << endl;
	}
	cout << endl;

	bool *rowsWithZeroValues = new bool[rowCount];
	bool *columnsWithZeroValues = new bool[columnCount];

	for (int index = 0; index < rowCount; index++) {
		rowsWithZeroValues[index] = false;
	}

	for (int index = 0; index < columnCount; index++) {
		columnsWithZeroValues[index] = false;
	}

	int element;
	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
		for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
			element = rows[rowIndex][columnIndex];
			if (element == 0) {
				rowsWithZeroValues[rowIndex] = true;
				columnsWithZeroValues[columnIndex] = true;
			}
		}
	}

	int rowsWithoutZeroCount = 0;
	int columnsWithoutZeroCount = 0;

	for (int index = 0; index < rowCount; index++) {
		if (rowsWithZeroValues[index] == false) {
			rowsWithoutZeroCount++;
		}
	}

	for (int index = 0; index < columnCount; index++) {
		if (columnsWithZeroValues[index] == false) {
			columnsWithoutZeroCount++;
		}
	}

	cout << "Rows without zero: " << rowsWithoutZeroCount << endl;
	cout << "Columns without zero: " << columnsWithoutZeroCount << endl << endl;

	return 0;
}
