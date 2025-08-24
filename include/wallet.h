#pragma once
#include <string>
#include <vector>

class Wallet {
private:
    double balance;
    std::vector<std::string> transactions;
public:
    Wallet();
    void deposit(double amount);
    void withdraw(double amount);
    void showBalance() const;
    void showTransactions() const;
};
