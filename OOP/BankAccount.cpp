#include "BankAccount.h"

BankAccount::BankAccount(std::string accNum, std::string accHolder, double bal) {
    accountNumber = accNum;
    accountHolderName = accHolder;
    balance = bal;
}

void BankAccount::displayAccountInfo() {
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder Name: " << accountHolderName << std::endl;
    std::cout << "Balance: $" << balance << std::endl;
}

// Hàm catch exception tập trung
void BankAccount::handleException(std::exception_ptr& eptr) {
    try {
        std::rethrow_exception(eptr);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool BankAccount::deposit(double amount) {
    try {
        if (amount < 0)
            throw std::invalid_argument("Deposit amount cannot be negative.");
        balance += amount;
        return true;
    } catch (...) {
        std::exception_ptr eptr = std::current_exception();
        handleException(eptr);
        return false;
    }
}

bool BankAccount::withdraw(double amount) {
    try {
        if (amount < 0)
            throw std::invalid_argument("Withdrawal amount cannot be negative.");
        if (amount > balance)
            throw std::runtime_error("Insufficient funds for withdrawal.");
        balance -= amount;
        return true;
    } catch (...) {
        std::exception_ptr eptr = std::current_exception();
        handleException(eptr);
        return false;
    }
}

void BankAccount::displayBalance() {
    std::cout << "Current Balance: $" << balance << std::endl;
}
