#include "TransactionService.h"
#include "TransactionDetails.h"
#include <iostream>
#include <iomanip>
#include <ctime>

TransactionService::TransactionService(TransactionRepository& repo) : repository(repo) {}

void TransactionService::showBalance() const {
    double bal = 0.0;
    for (const auto& tx : repository.getAllTransactions()) {
        if (tx.getType() == "Deposit") bal += tx.getAmount();
        else if (tx.getType() == "Withdrawal" || tx.getType() == "Bill Payment") bal -= tx.getAmount();
    }
    std::cout << "Current Balance: " << std::fixed << std::setprecision(2) << bal << " EGP\n";
}

void TransactionService::showTransactions() const {
    int count = 1;
    for (const auto& t : repository.getAllTransactions()) {
        std::string desc;
        char time_str[26];
        ctime_r(&t.getTimestamp(), time_str);
        time_str[24] = '\0'; // Remove newline
        if (t.getType() == "Deposit") {
            desc = "Deposited: " + std::to_string(t.getAmount());
        } else if (t.getType() == "Withdrawal") {
            desc = "Withdrew: " + std::to_string(t.getAmount());
        } else if (t.getType() == "Bill Payment") {
            desc = "Paid " + t.getDescription() + " bill: " + std::to_string(t.getAmount());
        }
        std::cout << count++ << ". " << desc << " on " << time_str << " (Status: " << t.getStatus() << ")\n";
    }
}

void TransactionService::showTransactionDetails(size_t index, const std::string& uname) const {
    auto transactions = repository.getAllTransactions();
    if (index < transactions.size()) {
        const auto& t = transactions[index];
        char time_str[26];
        ctime_r(&t.getTimestamp(), time_str);
        time_str[24] = '\0'; // Remove newline
        std::cout << "Transaction Details for User: " << uname << "\n";
        std::cout << "Type: " << t.getType() << '\n';
        std::cout << "Amount: " << std::fixed << std::setprecision(2) << t.getAmount() << " EGP\n";
        std::cout << "Description: " << t.getDescription() << '\n';
        std::cout << "Date: " << time_str << '\n';
        std::cout << "Status: " << t.getStatus() << '\n';
    } else {
        std::cout << "Invalid transaction number!\n";
    }
}

void TransactionService::deposit(double amount) {
    std::time_t now = std::time(nullptr);
    TransactionDetails tx("Deposit", amount, "Deposit transaction", now, "Completed");
    repository.addTransaction(tx);
    std::cout << "Deposited " << amount << " EGP successfully!\n";
}

void TransactionService::withdraw(double amount) {
    if (getBalance() >= amount) {
        std::time_t now = std::time(nullptr);
        TransactionDetails tx("Withdrawal", amount, "Withdrawal transaction", now, "Completed");
        repository.addTransaction(tx);
        std::cout << "Withdrew " << amount << " EGP successfully!\n";
    } else {
        std::cout << "Insufficient balance!\n";
    }
}

void TransactionService::payBill(double amount, const std::string& billType) {
    if (getBalance() >= amount) {
        std::time_t now = std::time(nullptr);
        TransactionDetails tx("Bill Payment", amount, billType + " bill payment", now, "Completed");
        repository.addTransaction(tx);
        std::cout << "Paid " << amount << " EGP for " << billType << " bill successfully!\n";
    } else {
        std::cout << "Insufficient balance!\n";
    }
}

double TransactionService::getBalance() const {
    double bal = 0.0;
    for (const auto& tx : repository.getAllTransactions()) {
        if (tx.getType() == "Deposit") bal += tx.getAmount();
        else if (tx.getType() == "Withdrawal" || tx.getType() == "Bill Payment") bal -= tx.getAmount();
    }
    return bal;
}

size_t TransactionService::getNumTransactions() const {
    return repository.getAllTransactions().size();
}