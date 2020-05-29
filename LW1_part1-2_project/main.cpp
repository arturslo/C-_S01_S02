#include <iostream> // iostream faila pieslēgšana, kurš satur standarta bibliotēkas
#include <iomanip>
// elementu aprakstus, kuri paredzēti datu ievadei un izvadei
using namespace std; // apraksts, pateicoties kuram programmai būs pieejami visi
// vārdi definēti failā iostream. Ša faila iekšā visi
// apraksti ir „paslēpti” vārdu telpā (namespace) ar
// nosaukumu std. Tai skaitā kļūst pieejami vārdi cin un
// cout.
int main() // programmas galvenā funkcija, ar kuru sākas tās izpilde
{ // bloka sākums
	int number1; // int tipa mainīgā а apraksts
	int number2;
	int resSquare; // int tipa mainīgā res apraksts
	cout << "Enter number1: "; // teksta "Enter number: " izvade uz ekrāna
	cin >> number1; // vesela skaitļa ievades gaidīšana no lietotāja un
	cout << "Enter number2: "; // teksta "Enter number: " izvade uz ekrāna
	cin >> number2; // vesela skaitļa ievades gaidīšana no lietotāja un
	// ievadītas vērtības ierakstīšana mainīgajā а
	resSquare = number1 * number1; // skaitļa (kas glabājas mainīgajā а) kvadrāta aprēķināšana, un
	int resSum = number1 + number2;
	int resSub = number1 - number2;
	int resMulti = number1 * number2;
	double resDiv = (double)number1 / (double)number2;



	// rezultāta ierakstīšana mainīgajā res
	cout << endl << "Square of " << number1 << " is " << resSquare << endl; // rezultāta izvade
	cout << number1 << " + " << number2 << " = " << resSum << endl;
	cout << number1 << " - " << number2 << " = " << resSub << endl;
	cout << number1 << " * " << number2 << " = " << resMulti << endl;
	cout << number1 << " / " << number2 << " = " << fixed << setprecision(2) << resDiv << endl;
	return 0; // vērtība 0, kuru atgriež funkcija main, un kura tiek interpretēta
	// kā tās darba veiksmīga pabeigšana
}
