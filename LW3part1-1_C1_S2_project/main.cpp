#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
// atrast tel numuru pec addresses

struct Shop
{
    char name[50];
    char address[100];
    char phoneNumber[10];

};

void readShopsFromFile(vector<Shop> &shops, const string &fileName);
void writeShopsToFile(vector<Shop> &shops, const string &fileName);

int main()
{
    const string FILE_NAME = "shops.txt";
    vector<Shop> shops;

    readShopsFromFile(shops, FILE_NAME);

    int menuChoice = 0;
    string menuInput = "";

    while (menuChoice != 5) {
        cout << endl;
        cout << "1. View data" << endl;
        cout << "2. Add data" << endl;
        cout << "3. Delete all" << endl;
        cout << "4. Find shop phone number by addres" << endl;
        cout << "5. Exit" << endl;
        cout << "choice: ";
        
        getline(cin, menuInput);
        cout << endl;
        menuChoice = stoi(menuInput);

        if (menuChoice == 1) {
            for (Shop shop : shops) {
                cout << "name: " << shop.name << endl;
                cout << "address: " << shop.address << endl;
                cout << "phone: " << shop.phoneNumber << endl;
                cout << endl;
            }
        } else if (menuChoice == 2) {
            Shop newShop;

            cout << "enter name: ";
            cin.getline(newShop.name, 50);
            cout << "enter address : ";
            cin.getline(newShop.address, 100);
            cout << "enter phone number: ";
            cin.getline(newShop.phoneNumber, 10);

            shops.push_back(newShop);
        } else if (menuChoice == 3) {
            shops.clear();
        } else if (menuChoice == 4) {
            char inputAddress[100];
            cout << "Enter address:" << endl;
            cin.getline(inputAddress, 100);
            cout << endl;

            for (Shop shop : shops) {
                if (strcmp(shop.address, inputAddress) == 0) {
                    cout << "phone: " << shop.phoneNumber << endl;
                }
            }

        } else if (menuChoice == 5) {
            writeShopsToFile(shops, FILE_NAME);
        }
    }

    return 0;
}


void readShopsFromFile(vector<Shop> &shops, const string &fileName)
{
    ifstream infile;
    infile.open(fileName, ios::in);
    if (!infile.fail()) {
        while (!infile.fail()) {
            Shop shop;
            infile.read(shop.name, sizeof(shop.name));
            infile.read(shop.address, sizeof(shop.address));
            infile.read(shop.phoneNumber, sizeof(shop.phoneNumber));
            if (infile.fail()) {
                break;
            }
            shops.push_back(shop);
        }
        infile.close();
    } else {
        cout << "File open for reading failed" << endl;
        infile.close();
    }
}

void writeShopsToFile(vector<Shop> &shops, const string &fileName)
{
    ofstream outfile;
    outfile.open("shops.txt", ios::out | ios::trunc);
    if (outfile.fail()) {
        cout << "File open for writing failed" << endl;
        outfile.close();
    } else {
        for (Shop shop : shops) {
            outfile.write(shop.name, sizeof(shop.name));
            outfile.write(shop.address, sizeof(shop.address));
            outfile.write(shop.phoneNumber, sizeof(shop.phoneNumber));
        }

        outfile.close();
    }
}
