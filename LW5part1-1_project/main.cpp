#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main()
{
	int arrayGenerationType;
	const int ARRAY_GENARATION_TYPE_MANUAL = 1;
	const int ARRAY_GENARATION_TYPE_AUTOMATIC = 2;

	cout << "Array generation:" << endl;
	cout << "1: Manual array element input" << endl;
	cout << "2: Automatic array element generation" << endl;
	cout << endl;
	cout << "Enter array element generation type: ";
	cin >> arrayGenerationType;

	if (
		arrayGenerationType != ARRAY_GENARATION_TYPE_MANUAL
		&& arrayGenerationType != ARRAY_GENARATION_TYPE_AUTOMATIC
	) {
		cout << "No such array generation type!" << endl;
		return 1;
	}

	int arraySize;

	cout << "Input array element count: ";
	cin >> arraySize;
	cout << endl;

	if (arraySize < 0) {
		cout << "Array element count cannot be less than 0" << endl;
		return 1;
	}

	float *elementArray = new float[arraySize];

	if (arrayGenerationType == ARRAY_GENARATION_TYPE_MANUAL) {
		for (int index = 0; index < arraySize; index++) {
			cout << "input element <float>: ";
			cin >> elementArray[index];
		}

		cout << endl;
	}

	if (arrayGenerationType == ARRAY_GENARATION_TYPE_AUTOMATIC && arraySize > 0) {
		float min;
		float max;

		cout << "Enter range: " << endl;
		cout << "Range start <float> : ";
		cin >> min;
		cout << "Range end <float> : ";
		cin >> max;

		if (min > max) {
			cout << "Range start cannot be less than Range end" << endl;
			return 1;
		}

		cout << "range [" << min << ";" << max << "]" << endl << endl;

		srand(time(NULL));
		float range = max - min;
		float random;
		float fresult;

		for (int index = 0; index < arraySize; index++) {
			random = (float)rand() / (float)RAND_MAX;
			fresult = (random * range) + min;
			elementArray[index] = fresult;
		}
	}

	cout << "Starting array:" << endl << endl;
	for (int index = 0; index < arraySize; index++) {
		cout << elementArray[index] << " ";
	}
	cout << endl << endl;

	float evenNumberMultiplication = 1.00;
	int evenNumberMultiplicationCount = -1;

	for (int number = 1; number <= arraySize; number++) {
		if (number % 2 != 0) {
			continue;
		}

		evenNumberMultiplication *= elementArray[number - 1];
		evenNumberMultiplicationCount++;
	}

	string evenNumberMultiplicationString = to_string(evenNumberMultiplication);
	if (evenNumberMultiplicationCount < 1) {
		evenNumberMultiplication = 0.00;
		evenNumberMultiplicationCount = 0;
		evenNumberMultiplicationString = "No result";
	}

	cout << "Even number multiplication result: " << evenNumberMultiplicationString << endl;

	float betweenZeroElementsSum = 0.00;
	float betweenZeroElementsTempSum = 0.00;
	float arrayElement;
	bool isElementZero;
	bool isFirstZeroFound = false;
	bool isSecondZeroFound = false;

	for (int index = 0; index < arraySize; index++) {
		arrayElement = elementArray[index];
		isElementZero = arrayElement == 0.00;

		if (isElementZero && !isFirstZeroFound) {
			isFirstZeroFound = true;
			continue;
		}

		if (!isElementZero && isFirstZeroFound) {
			betweenZeroElementsTempSum += arrayElement;
			continue;
		}

		if (isElementZero && isFirstZeroFound) {
			isSecondZeroFound = true;
			betweenZeroElementsSum += betweenZeroElementsTempSum;
			betweenZeroElementsTempSum = 0.00;
			continue;
		}
	}

	string betweenZeroElementsSumString = to_string(betweenZeroElementsSum);
	if (!isSecondZeroFound) {
		betweenZeroElementsSumString = "No result";
	}

	cout << "Between zero elements sum: " << betweenZeroElementsSumString << endl;

	float tempElement;
	bool needToContinue;
	for (int index1 = 0; index1 < arraySize; index1++) {
		needToContinue = false;
		for (int index2 = 1; index2 < arraySize; index2++) {
			if (
				elementArray[index2 - 1] < 0
				&& elementArray[index2] >= 0
			) {
				tempElement = elementArray[index2 - 1];
				elementArray[index2 - 1] = elementArray[index2];
				elementArray[index2] = tempElement;
				needToContinue = true;
			}
		}

		if (!needToContinue) {
			break;
		}
	}

	cout << "Positive values first transformed array:" << endl;
	for (int index = 0; index < arraySize; index++) {
		cout << elementArray[index] << " ";
	}
	cout << endl << endl;

	return 0;
}
