#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	double x;
	cout << "input x <double> -> ";
	cin >> x;
	cout << endl;

	double result;

	if (x > -1 && x < 0) {
		cout << "matched condition 1" << endl;
		result = 1 / pow(x + 1, 3);
	}
	else if (x >= 0 && x <= 1) {
		cout << "matched condition 2" << endl;
		result = pow(cos((x * M_PI / 180) - 1), 2);
	}
	else {
		cout << "matched condition default" << endl;
		result = log(pow(x, 2) + 3);
	}

	cout << "result is " << fixed << setprecision(20) << result << endl;

	return 0;
}
