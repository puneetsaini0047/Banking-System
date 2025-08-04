#include "admin.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void Admin::adminLogin() {
    string password;
    cout << "\n=== Admin Login ===\n";
    cout << "Enter Admin Password: ";
    getline(cin, password);
    if (password == "admin123") { // Simple password for demonstration
        cout << "Admin Login Successful!\n";
        adminMenu();
    } else {
        cout << "Invalid Admin Password!\n";
    }
}

void Admin::adminMenu() {
    int choice;
    do {
        cout << "\n=== Admin Menu ===\n"
             << "1. View All Accounts\n"
             << "2. Search for Account\n"
             << "3. Delete Account\n"
             << "4. View Loan Applications\n"
             << "5. Logout\n"
             << "Enter your choice: ";
        cin >> choice;
        while (cin.fail()) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;
        }
        cin.ignore();
        // clearScreen(); // You would call your clear screen function here

        switch (choice) {
            case 1: viewAllAccounts(); break;
            case 2: searchForAccount(); break;
            case 3: deleteAccount(); break;
            case 4: viewLoanApplications(); break;
            case 5: cout << "Logging out from Admin panel...\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void Admin::viewAllAccounts() {
    cout << "\n=== All Bank Accounts ===\n";
    ifstream file("Bank-Of-India.txt");
    int latestAccountCode = 0;
    if(file.is_open()){
        file >> latestAccountCode;
        file.close();
    }

    // Assuming account codes start from 101
    for (int i = 101; i <= latestAccountCode; ++i) {
        string accNum = "BankOfIndia" + to_string(i);
        ifstream accFile(accNum + ".txt");
        if(accFile.is_open()){
            bankAccount acc;
            acc.setAccountNumber(accNum); // Set the account number
            acc.loadFromFile();
            cout << "Account Number: " << acc.getAccountNumber()
                 << ", Name: " << acc.getAccountHolderName()
                 << ", Balance: " << acc.getBalance() << endl;
            accFile.close();
        }
    }
}

void Admin::searchForAccount() {
    string accNum;
    cout << "\n=== Search for Account ===\n";
    cout << "Enter Account Number to search: ";
    getline(cin, accNum);

    ifstream file(accNum + ".txt");
    if(file.is_open()){
        file.close();
        bankAccount acc;
        // THIS IS THE CORRECTED PART
        acc.setAccountNumber(accNum);
        acc.loadFromFile();
        acc.accountDetails();
    } else {
        cout << "Account not found!\n";
    }
}

void Admin::deleteAccount() {
    string accNum;
    cout << "\n=== Delete Account ===\n";
    cout << "Enter Account Number to delete: ";
    getline(cin, accNum);

    string filename = accNum + ".txt";
    if (remove(filename.c_str()) == 0) {
        cout << "Account deleted successfully!\n";
    } else {
        cout << "Error deleting account or account not found!\n";
    }
}

void Admin::viewLoanApplications() {
    cout << "\n=== Loan Applications ===\n";
    ifstream file("loan_applications.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No loan applications found or error opening file.\n";
    }
}