#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>

class bankAccount {
private:
    std::string bankName = "BankOfIndia";
    int bankCode;
    std::string accountHolderName;
    std::string accountNumber;
    std::string accountPassword; // Hashed password
    std::string addharNumber;
    std::string email;
    std::string phoneNumber;
    double balance;
    std::vector<std::string> transactionHistory;

    // Password hashing function
    std::string hashPassword(const std::string& password);

public:
    // File operations
    void savetoFile();
    void loadFromFile();

    // Main menu and user actions
    void mainMenu();
    void createAccount();
    void loginBankAccount();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();
    void accountDetails();
    void allTransactionHistory();
    void transferFunds();
    void applyForLoan();

    // ADD THIS NEW LINE TO YOUR FILE
    void setAccountNumber(const std::string& accNum);

    // Getter methods for admin
    std::string getAccountNumber() const { return accountNumber; }
    std::string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }
};

#endif // BANKACCOUNT_H