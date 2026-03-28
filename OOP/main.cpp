#include <iostream>
#include "BankAccount.h"

int main() {
    BankAccount account1("123456789", "John Doe", 1000.0);
    account1.displayAccountInfo();

    std::cout << "\nDepositing $500..." << std::endl;
    if (account1.deposit(500)) {
        std::cout << "Deposit successful." << std::endl;
    }
    account1.displayAccountInfo();

    std::cout << "\nWithdrawing $200..." << std::endl;
    if (account1.withdraw(200)) {
        std::cout << "Withdrawal successful." << std::endl;
    }
    account1.displayAccountInfo();

    std::cout << "\nAttempting to withdraw $1500..." << std::endl;
    if (!account1.withdraw(1500)) {
        std::cout << "Withdrawal failed due to insufficient funds." << std::endl;
    }
    account1.displayAccountInfo();

    return 0;
}
