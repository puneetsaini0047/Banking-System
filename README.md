Banking System:
A C++ command-line application for managing bank accounts and transactions with permanent data storage.
-----------------------------------------------
Features:
Account Management: Create and manage bank accounts.
Transactions: Deposit and withdraw money.
Balance Inquiry: Check current account balances.
Data Persistence: Saves all records to text files.

----------------------------------------------
How to Run
Compile:  g++ main.cpp bankAccount.cpp admin.cpp -o BankingSystem
Run: ./BankingSystem

-----------------------------------------------
Project Structure
main.cpp: Main menu and program entry.
bankAccount.h / bankAccount.cpp: Logic for accounts and transactions.
admin.h / admin.cpp: System administrative functions.
*.txt: Permanent storage files for account data.
