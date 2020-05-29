#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	printf("Enter input data:\n\n");

	int triangleBase;
	int triangleHeight;

	printf("Enter base of a triangle: ");
	scanf("%i", &triangleBase);
	printf("Enter height of a triangle: ");
	scanf("%i", &triangleHeight);

	double triangleArea = 0.5 * triangleBase * triangleHeight;
	printf("\nArea of the triangle is %.7f sq.cm\n", triangleArea);
}
