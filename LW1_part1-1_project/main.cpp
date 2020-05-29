#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> // faila stdio.h pieslēgšana, kur ir aprakstīta ievades
// funkcija scanf un izvades funkcija printf
int main() // programmas galvenā funkcija, ar kuru sākas tās izpilde
{ // bloka sākums
	int number1; // int tipa mainīgā а apraksts
	int number2;
	int squareResult; // int tipa mainīgā res apraksts
	printf("Enter number1: "); // teksta "Enter number: " izvade uz ekrāna
	scanf("%i", &number1); // vesela skaitļa ievades gaidīšana no lietotāja un
	printf("Enter number2: "); // teksta "Enter number: " izvade uz ekrāna
	scanf("%i", &number2); // vesela skaitļa ievades gaidīšana no lietotāja un
	// ievadītas vērtības ierakstīšana mainīgajā а
	squareResult = number1 * number1; // skaitļa (kas glabājas mainīgajā а) kvadrāta aprēķināšana, un
	// rezultāta ierakstīšana mainīgajā res

	int sumResult = number1 + number2;
	int subtractionResult = number1 - number2;
	int multiplicationResult = number1 * number2;
	double divisionResult = (double)number1 / (double)number2;

	printf("Square of %i is %i\n", number1, squareResult); // rezultāta izvade uz ekrāna
	printf("Sum of a %i and b %i is %i\n", number1, number2, sumResult);
	printf("Subtraction of a %i and b %i is %i\n", number1, number2, subtractionResult);
	printf("Multiplication of a %i and b %i is %i\n", number1, number2, multiplicationResult);
	printf("Division result of a %i and b %i is %.2f\n", number1, number2, divisionResult);

	return 0; // vērtība 0, kuru atgriež funkcija main, un kura tiek interpretēta
	// kā tās darba veiksmīga pabeigšana
}
