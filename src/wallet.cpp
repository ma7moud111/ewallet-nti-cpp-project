#include "wallet.h"
#include <iostream>
#include <iomanip>

Wallet::Wallet() : balance(0.0) {}

void Wallet::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "Amount must be positive.\n";
        return;
    }
    balance += amount;
    transactions.push_back("Deposited: " + std::to_string(amount));
    std::cout << "Deposited successfully.\n";
}

void Wallet::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "Amount must be positive.\n";
        return;
    }
    if (amount > balance) {
        std::cout << "Insufficient funds!\n";
        return;
    }
    balance -= amount;
    transactions.push_back("Withdrew: " + std::to_string(amount));
    std::cout << "Withdrawal successful.\n";
}

void Wallet::showBalance() const {
    std::cout << "Current Balance: " << std::fixed << std::setprecision(2) << balance << " EGP\n";
}

void Wallet::showTransactions() const {
    if (transactions.empty()) {
        std::cout << "No transactions yet.\n";
        return;
    }
    std::cout << "Transaction History:\n";
    for (const auto& t : transactions) {
        std::cout << "- " << t << '\n';
    }
}
