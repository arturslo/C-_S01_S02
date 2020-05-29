#include <iostream>
#include <cmath>

using namespace std;

int main()
{

	int a;
	int b;

	cout << "input a <int> -> ";
	cin >> a;
	cout << "input b <int> -> ";
	cin >> b;
	cout << endl;

	if (a > b) {
		cout << "number a cannot be larger than number b" << endl;
		return 1;
	}

	int preciseSquareNumberCount = 0;

	for (int number = a; number <= b; number++) {

		if (number < 0) {
			continue;
		}

		double squareRootOfNumber = sqrt(number);
		double reminder = fmod(sqrt(number), 1);

		if (0 == reminder) {
			preciseSquareNumberCount++;
			cout << "Number " << number << " is precise square of " << squareRootOfNumber << endl;
		}
	}

	cout << endl << "preciseSquareNumberCount: " << preciseSquareNumberCount << endl;
	return 0;
}
