#include <iostream>
#include <string>
#include <iomanip>

typedef char userInput[256];

using namespace std;
// Struktūras lauki: grāmatas inventāra numurs, nosaukums, lapu skaits. Operācija: atrast grāmatas inventāra numuru pēc ievadīta nosaukuma.

struct Book
{
    char inventoryNumber[7];
    char title[101];
    int pageCount;
};

enum class Choice : int
{
    showBooks = 1,
    findBookByTitle = 2,
    quit = 3
};

int main()
{

    const int BOOK_ARRAY_SIZE = 2;
    Book bookArray[BOOK_ARRAY_SIZE];

    for (int i = 0; i < BOOK_ARRAY_SIZE; i++) {
        cout << "Book " << i + 1 << " :" << endl;
        cout << "inventory number: ";
        cin.getline(bookArray[i].inventoryNumber, 7);
        
        if (cin.fail()) {
            bookArray[i].inventoryNumber[0] = '\0';
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
        cout << "title: ";
        cin.getline(bookArray[i].title, 101);

        if (cin.fail()) {
            bookArray[i].title[0] = '\0';
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "page count: ";
        cin >> bookArray[i].pageCount;
        cin.ignore();

        if (cin.fail()) {
            bookArray[i].pageCount = 0;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << endl;
    }


    int choice = 0;
    userInput choiceInput;
    while (choice != (int)Choice::quit) {
        cout << "Press 1 to show books" << endl;
        cout << "Press 2 to find book by title" << endl;
        cout << "Press 3 to quit" << endl;
        cout << "Input choice: ";

        cin.getline(choiceInput, 256);
        choice = atoi(choiceInput);
        cout << endl;

        if (choice == (int)Choice::showBooks) {
            for (int i = 0; i < BOOK_ARRAY_SIZE; i++) {
                cout << "Book " << i + 1 << endl;
                cout << "title: " << bookArray[i].title << endl;
                cout << "inventory number: " << setw(6) << left << bookArray[i].inventoryNumber;
                cout << " page count: " << setw(4) << left << bookArray[i].pageCount;
                cout << endl;
                cout << "-----------------------------------------" << endl << endl;
            }
            cout << endl;

        } else if (choice == (int)Choice::findBookByTitle) {
            cout << "Title to find: ";
            cin.getline(choiceInput, 256);
            cout << endl;

            for (int i = 0; i < BOOK_ARRAY_SIZE; i++) {
                if (strncmp(bookArray[i].title, choiceInput, 100) == 0) {
                    cout << "inventory number: " << setw(6) << left << bookArray[i].inventoryNumber << endl;;
                    cout << "------------------------" << endl << endl;
                }
            }
            cout << endl;
        }

    }

    return 0;
}
