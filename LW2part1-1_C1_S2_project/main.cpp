/*
Uzrakstīt funkciju, kas teksta virknē pēc katra norādīta simbola ievieto norādīto teksta apakšvirkni.
Uzrakstīt programmu, kas pieņem no lietotāja teksta virkņu kopumu, simbolu un teksta apakšvirkni,
visās kopuma teksta virknēs ievieto pēc norādīta simbola (visur, kur šis simbols tiek sastapts teksta virknē)
norādīto teksta apakšvirkni un izvada uz ekrāna pārveidotu teksta virkņu kopumu.
Izmantot uzrakstīto funkciju.
*/

#include <iostream>;
#include <string>

using namespace std;

const int STRING_COUNT = 2;
const int CSTRING_MAX_LENGTH = 101;
const int APPEND_CSTRING_MAX_LENGTH = 101;

void printString(const char* inputString, const int& maxStringLength, const bool& printTerminationCharacter = false);
void printString(const string& inputString);
void appendStringAfterCharacter(char* inputString, const int& maxInputStringLength, const char& findChar, const char* appendString);
void appendStringAfterCharacter(string& inputString, const char& findChar, const string& appendString);

int main()
{
    char cstringArray[STRING_COUNT][CSTRING_MAX_LENGTH];

    for (int i = 0; i < STRING_COUNT; i++) {
        cout << "Input line: " << i + 1 << endl;
        cin.getline(cstringArray[i], CSTRING_MAX_LENGTH);
    }

    char findChar;
    cout << "Input character: ";
    cin.get(findChar);
    cin.clear();
    cin.ignore(10000, '\n');

    char appendCstring[APPEND_CSTRING_MAX_LENGTH];
    cout << "Input string to append after symbol:" << endl;
    cin.getline(appendCstring, APPEND_CSTRING_MAX_LENGTH);

    string stringArray[STRING_COUNT];
    for (int i = 0; i < STRING_COUNT; i++) {
        stringArray[i] = cstringArray[i];
    }

    string appendString = appendCstring;

    for (int i = 0; i < STRING_COUNT; i++) {
        appendStringAfterCharacter(cstringArray[i], CSTRING_MAX_LENGTH, findChar, appendCstring);
    }

    for (int i = 0; i < STRING_COUNT; i++) {
        appendStringAfterCharacter(stringArray[i], findChar, appendCstring);
    }

    int choice;
    do {
        cout << endl;
        cout << "1: print cstring arrays" << endl;
        cout << "2: print string arrays" << endl;
        cout << "3: exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << endl;

        if (choice == 1) {
            for (int i = 0; i < STRING_COUNT; i++) {
                printString(cstringArray[i], CSTRING_MAX_LENGTH);
            }
        } else if (choice == 2) {
            for (int i = 0; i < STRING_COUNT; i++) {
                printString(stringArray[i]);
            }
        }

    } while (choice != 3);

    return 0;
}

void printString(const char* inputString, const int& maxStringLength, const bool& printTerminationCharacter)
{
    for (int i = 0; i < maxStringLength; i++) {
        if (inputString[i] == '\0') {
            if (printTerminationCharacter == false) {
                break;
            }
            cout << "\\0";
            break;
        }
        cout << inputString[i];
    }
    cout << endl;
}

void printString(const string& inputString)
{
    cout << inputString << endl;
}

void appendStringAfterCharacter(char* inputString, const int& maxInputStringLength, const char& findChar, const char* appendString)
{
    int inputStringLength = strlen(inputString);
    int appendStringLength = strlen(appendString);

    for (int i1 = 0; i1 < inputStringLength; i1++) {
        if (inputString[i1] != findChar) {
            continue;
        }
        if (inputStringLength + 1 + appendStringLength > maxInputStringLength) {
            break;
        }
        for (int i2 = inputStringLength; i2 > i1; i2--) {
            inputString[i2 + appendStringLength] = inputString[i2];
        }
        for (int i3 = 0; i3 < appendStringLength; i3++) {
            inputString[i1 + 1 + i3] = appendString[i3];
        }

        inputStringLength += appendStringLength;
        i1 += appendStringLength;
    }
}

void appendStringAfterCharacter(string& inputString, const char& findChar, const string& appendString)
{
    size_t foundAtIndex = inputString.find(findChar);
    while (foundAtIndex != string::npos) {
        inputString.insert(foundAtIndex + 1, appendString);
        foundAtIndex = inputString.find(findChar, foundAtIndex + 1);
    }
}
