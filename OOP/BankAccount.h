#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class BankAccount {
private:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;
    void handleException(std::exception_ptr& eptr);
public:
    BankAccount(std::string accNum, std::string accHolder, double bal);
    void displayAccountInfo();
    bool deposit(double amount);
    bool withdraw(double amount);
    void displayBalance();
};



