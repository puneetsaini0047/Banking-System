#ifndef ADMIN_H
#define ADMIN_H

#include "bankAccount.h"
#include <vector>

class Admin {
public:
    void adminLogin();
    void adminMenu();
    void viewAllAccounts();
    void searchForAccount();
    void deleteAccount();
    void viewLoanApplications();
};

#endif // ADMIN_H