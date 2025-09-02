#ifndef TRANSACTION_SERVICE_H
#define TRANSACTION_SERVICE_H

#include "TransactionRepository.h"
#include <vector>
#include <cstddef>

class TransactionService {
public:
    explicit TransactionService(TransactionRepository& repo);
    void showBalance() const;
    void showTransactions() const;
    void showTransactionDetails(size_t index, const std::string& uname) const;
    void deposit(double amount);
    void withdraw(double amount);
    void payBill(double amount, const std::string& billType);
    double getBalance() const;
    size_t getNumTransactions() const;

private:
    TransactionRepository& repository;
};

#endif