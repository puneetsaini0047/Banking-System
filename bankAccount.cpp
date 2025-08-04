#include "bankAccount.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

// A simple XOR-based hashing function
string bankAccount::hashPassword(const string& password) {
    string hashedPassword = password;
    for (char& c : hashedPassword) {
        c = c ^ 0x5A; // XOR with a secret key
    }
    return hashedPassword;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void bankAccount::savetoFile() {
    ofstream file(accountNumber + ".txt");
    if (file.is_open()) {
        file << accountHolderName << endl;
        file << accountNumber << endl;
        file << hashPassword(accountPassword) << endl; // Save hashed password
        file << addharNumber << endl;
        file << email << endl;
        file << phoneNumber << endl;
        file << balance << endl;
        for (const auto& transaction : transactionHistory) {
            file << transaction << endl;
        }
        file.close();
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

void bankAccount::loadFromFile() {
    ifstream file(accountNumber + ".txt");
    if (file.is_open()) {
        getline(file, accountHolderName);
        getline(file, accountNumber);
        getline(file, accountPassword); // Load hashed password
        getline(file, addharNumber);
        getline(file, email);
        getline(file, phoneNumber);
        file >> balance;
        file.ignore();
        string transaction;
        while (getline(file, transaction)) {
            transactionHistory.push_back(transaction);
        }
        file.close();
    } else {
        cout << "Error: Unable to open file for reading." << endl;
    }
}

// This is the new function you are adding
void bankAccount::setAccountNumber(const std::string& accNum) {
    accountNumber = accNum;
}

void bankAccount::mainMenu() {
    int choice;
    do {
        cout << "\n=== Main Menu ===\n"
             << "1. Deposit Money\n"
             << "2. Withdraw Money\n"
             << "3. Check Balance\n"
             << "4. Account Details\n"
             << "5. Transaction History\n"
             << "6. Transfer Funds\n"
             << "7. Apply for Loan\n"
             << "8. Logout\n"
             << "Enter your choice: ";
        cin >> choice;
        while (cin.fail()) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;
        }
        cin.ignore();
        clearScreen();

        switch (choice) {
            case 1: depositMoney(); break;
            case 2: withdrawMoney(); break;
            case 3: checkBalance(); break;
            case 4: accountDetails(); break;
            case 5: allTransactionHistory(); break;
            case 6: transferFunds(); break;
            case 7: applyForLoan(); break;
            case 8: cout << "Logging out...!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

void bankAccount::createAccount() {
    cout << "\n=== Create Account ===\n";
    cout << "Enter Your Full Name: ";
    getline(cin, accountHolderName);
    cout << "Enter Email Id: ";
    getline(cin, email);
    cout << "Enter Phone Number: ";
    getline(cin, phoneNumber);
    cout << "Enter Aadhar Number: ";
    getline(cin, addharNumber);
    cout << "Enter Account Password: ";
    getline(cin, accountPassword);

    balance = 500.0;
    ifstream file("Bank-Of-India.txt");
    if (file.is_open()) {
        file >> bankCode;
        file.close();
    }
    bankCode++; // Increment the bank code for the new account

    ofstream outfile("Bank-Of-India.txt");
    if(outfile.is_open()){
        outfile << bankCode;
        outfile.close();
    }

    accountNumber = bankName + to_string(bankCode);
    transactionHistory.push_back("Initial Deposit: " + to_string(balance));

    cout << "\nAccount Created Successfully!\n"
         << "Account Number: " << accountNumber << "\n"
         << "Minimum Balance: " << balance << "\n";
    savetoFile();
}

void bankAccount::loginBankAccount() {
    string enteredAccountNumber, enteredPassword;
    cout << "\n=== Login ===\n";
    cout << "Enter Account Number: ";
    getline(cin, enteredAccountNumber);
    accountNumber = enteredAccountNumber;

    ifstream file(enteredAccountNumber + ".txt");
    if (file.is_open()) {
        file.close();
        loadFromFile();
        cout << "Enter Account Password: ";
        getline(cin, enteredPassword);

        if (accountPassword == hashPassword(enteredPassword)) {
            cout << "Login Successful!\n";
            mainMenu();
        } else {
            cout << "Invalid Password!\n";
        }
    } else {
        cout << "Account not found!\n";
    }
}

void bankAccount::depositMoney() {
    double amount;
    cout << "\n=== Deposit Money ===\n";
    cout << "Enter Amount to Deposit: ";
    cin >> amount;
    if (cin.fail() || amount <= 0) {
        cout << "Invalid Amount!\n";
        cin.clear();
        cin.ignore(256, '\n');
        return;
    }
    cin.ignore();
    balance += amount;
    transactionHistory.push_back("Deposit: +" + to_string(amount));
    cout << "Deposit Successful!\n"
         << "New Balance: " << balance << endl;
    savetoFile();
}

void bankAccount::withdrawMoney() {
    double amount;
    cout << "\n=== Withdraw Money ===\n";
    cout << "Enter Amount to Withdraw: ";
    cin >> amount;
    if (cin.fail() || amount <= 0 || amount > balance) {
        cout << "Invalid Amount or Insufficient Balance!\n";
        cin.clear();
        cin.ignore(256, '\n');
        return;
    }
    cin.ignore();
    balance -= amount;
    transactionHistory.push_back("Withdrawal: -" + to_string(amount));
    cout << "Withdrawal Successful!\n"
         << "New Balance: " << balance << endl;
    savetoFile();
}

void bankAccount::checkBalance() {
    cout << "\n=== Check Balance ===\n";
    cout << "Current Balance: " << balance << endl;
}

void bankAccount::accountDetails() {
    cout << "\n=== Account Details ===\n"
         << "Account Holder Name: " << accountHolderName << endl
         << "Account Number: " << accountNumber << endl
         << "Aadhar Number: " << addharNumber << endl
         << "Email Id: " << email << endl
         << "Phone Number: " << phoneNumber << endl
         << "Current Balance: " << balance << endl;
}

void bankAccount::allTransactionHistory() {
    cout << "\n=== Transaction History ===\n";
    for (const auto& transaction : transactionHistory) {
        cout << transaction << endl;
    }
}

void bankAccount::transferFunds() {
    string recipientAccountNumber;
    double amount;
    cout << "\n=== Transfer Funds ===\n";
    cout << "Enter Recipient's Account Number: ";
    getline(cin, recipientAccountNumber);
    cout << "Enter Amount to Transfer: ";
    cin >> amount;
    if (cin.fail() || amount <= 0 || amount > balance) {
        cout << "Invalid Amount or Insufficient Balance!\n";
        cin.clear();
        cin.ignore(256, '\n');
        return;
    }
    cin.ignore();

    ifstream recipientFile(recipientAccountNumber + ".txt");
    if (recipientFile.is_open()) {
        recipientFile.close();
        // Recipient account exists, now process the transfer
        balance -= amount;
        transactionHistory.push_back("Transfer to " + recipientAccountNumber + ": -" + to_string(amount));
        savetoFile();

        // Update recipient's account
        bankAccount recipient;
        recipient.setAccountNumber(recipientAccountNumber); // Use the new function here too!
        recipient.loadFromFile();
        recipient.balance += amount;
        recipient.transactionHistory.push_back("Transfer from " + accountNumber + ": +" + to_string(amount));
        recipient.savetoFile();

        cout << "Transfer Successful!\n"
             << "Your New Balance: " << balance << endl;
    } else {
        cout << "Recipient Account not found!\n";
    }
}

void bankAccount::applyForLoan() {
    double loanAmount;
    cout << "\n=== Apply for Loan ===\n";
    cout << "Enter Loan Amount: ";
    cin >> loanAmount;
    if (cin.fail() || loanAmount <= 0) {
        cout << "Invalid Amount!\n";
        cin.clear();
        cin.ignore(256, '\n');
        return;
    }
    cin.ignore();

    ofstream loanFile("loan_applications.txt", ios::app);
    if (loanFile.is_open()) {
        loanFile << accountNumber << "," << accountHolderName << "," << loanAmount << endl;
        loanFile.close();
        cout << "Loan application submitted successfully!\n";
    } else {
        cout << "Error submitting loan application!\n";
    }
}