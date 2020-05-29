#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

	cout << "Input precission e <double>: ";
	double e;
	cin >> e;
	cout << endl;

	if (e <= 0) {
		cout << "Enter decimal number larger than 0" << endl;
		return -1;
	}

	double sum = 1.00;

	int number = 3;
	int index = 0;

	while (1 / (double)number >= e) {

		if (index % 2 == 0) {
			cout << sum << " - 1 / " << number << endl;
			sum -= 1 / (double)number;
		} else {
			cout << sum << " + 1 / " << number << endl;
			sum += 1 / (double)number;
		}

		number += 2;
		index++;
	}

	cout << endl << "sum:  " << fixed << setprecision(20) << sum << endl;
	cout << "pi / 4: " << M_PI / 4 << endl;


	return 0;
}
