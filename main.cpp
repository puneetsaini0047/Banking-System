#include "bankAccount.h"
#include "admin.h"
#include <iostream>

using namespace std;

int main() {
    int choice;

    do {
        cout << "\n=== Welcome to Bank Of India ===\n"
             << "1. Customer Login\n"
             << "2. Create Account\n"
             << "3. Admin Login\n"
             << "4. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        while (cin.fail()) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;
        }
        cin.ignore();
        // clearScreen(); // You can add the clear screen function call here if you like

        bankAccount account;
        Admin admin;

        switch (choice) {
            case 1:
                account.loginBankAccount();
                break;
            case 2:
                account.createAccount();
                break;
            case 3:
                admin.adminLogin();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}