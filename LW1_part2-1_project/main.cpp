#include <iostream>
using namespace std;

int main()
{
	int rectangleWidth;
	int rectangleHeight;

	cout << "Enter input data:" << endl << endl;

	cout << "Rectangle width <cm> -> ";
	cin >> rectangleWidth;
	cout << "Rectangle height <cm> -> ";
	cin >> rectangleHeight;

	int areaOfRectangle = rectangleWidth * rectangleHeight;

	cout << endl << "Area of the rectangle is " << areaOfRectangle << " sq.cm" << endl;
}
