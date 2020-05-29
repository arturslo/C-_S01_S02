#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
/*
No 3
     sin 2a + sin 5a - sin 3a
z1 = ------------------------    z2 = 2sin a
     cos a + 1 - 2sin^2 2a
*/
int main()
{
	cout << "Enter input data:" << endl << endl;
	cout << "Alpha angle <deg> -> ";
	int alpha;
	cin >> alpha;
	cout << endl;

	double z1 = (sin(2 * alpha * M_PI / 180) + sin(5 * alpha * M_PI / 180) - sin(3 * alpha * M_PI / 180))
		/ (cos(alpha * M_PI / 180) + 1 - 2 * pow(sin(2 * alpha * M_PI / 180), 2));

	double z2 = 2 * sin(alpha * M_PI / 180);

	cout << "z1 = " << fixed << setprecision(20) << z1 << endl;
	cout << "z2 = " << fixed << setprecision(20) << z2 << endl;

	bool approximatelyEqual = fabs(z1 - z2) < 1e-10;

	cout << "z1 and z2 are approximately equal: " << boolalpha << approximatelyEqual << endl;

	return 0;
}
