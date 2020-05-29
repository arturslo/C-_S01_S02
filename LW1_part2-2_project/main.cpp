#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	const double PI = 3.1416;

	printf("Enter input data:\n\n");
	printf("Circle radiuss <cm> -> ");

	int circleRadiuss;
	scanf("%i", &circleRadiuss);

	double circleArea = PI * circleRadiuss * circleRadiuss;

	printf("\nArea of the circle is %.4f sq.cm\n", circleArea);
}
