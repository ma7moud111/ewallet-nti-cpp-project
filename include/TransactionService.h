#ifndef TRANSACTION_SERVICE_H
#define TRANSACTION_SERVICE_H
#include "TransactionRepository.h"
#include <vector>
#include <cstddef>
#include <memory>

class UserRepository;

class TransactionService {
private:
    TransactionRepository& repository;
    std::string currentUsername;
    UserRepository* userRepository; // Added for transfer validation
    std::vector<TransactionDetails> getUserTransactions() const;

public:
    explicit TransactionService(TransactionRepository& repo, const std::string& username, UserRepository* userRepo = nullptr);
    
    void showBalance() const;
    void showTransactions() const;
    std::unique_ptr<TransactionDetails> getTransaction(size_t index) const;
    void deposit(double amount);
    void withdraw(double amount);
    void payBill(double amount, const std::string& billType);
    bool transferMoney(double amount, const std::string& recipientUsername);
    double getBalance() const;
    size_t getNumTransactions() const;
};

#endif