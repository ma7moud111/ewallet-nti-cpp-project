#include "TransactionService.h"
#include "TransactionDetails.h"
#include "TransactionType.h"
#include "UserRepository.h"
#include "User.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <memory>

TransactionService::TransactionService(TransactionRepository& repo, const std::string& username, UserRepository* userRepo) 
    : repository(repo), currentUsername(username), userRepository(userRepo) {}

std::vector<TransactionDetails> TransactionService::getUserTransactions() const {
    return repository.getTransactionsByUser(currentUsername);
}

void TransactionService::showBalance() const {
    std::cout << "Current Balance: " << std::fixed << std::setprecision(2) 
              << getBalance() << " EGP\n";
}

void TransactionService::showTransactions() const {
    auto transactions = getUserTransactions();
    int count = 1;
    
    for (const auto& t : transactions) {
        std::string desc;
        char time_str[26];
        ctime_r(&t.getTimestamp(), time_str);
        time_str[24] = '\0'; // Remove newline
        
        if (t.getType() == TransactionType::Deposit) {
            desc = "Deposited: " + std::to_string(t.getAmount());
        } else if (t.getType() == TransactionType::Withdrawal) {
            desc = "Withdrew: " + std::to_string(t.getAmount());
        } else if (t.getType() == TransactionType::BillPayment) {
            desc = "Paid " + t.getDescription() + " bill: " + std::to_string(t.getAmount());
        } else if (t.getType() == TransactionType::Transfer) {
            desc = "Transfer: " + t.getDescription() + ": " + std::to_string(t.getAmount());
        }
        
        std::cout << count++ << ". " << desc << " on " << time_str 
                  << " (Status: " << t.getStatus() << ")\n";
    }
}

std::unique_ptr<TransactionDetails> TransactionService::getTransaction(size_t index) const {
    auto transactions = getUserTransactions();
    if (index < transactions.size()) {
        return std::make_unique<TransactionDetails>(transactions[index]);
    }
    return nullptr;
}

void TransactionService::deposit(double amount) {
    std::time_t now = std::time(nullptr);
    TransactionDetails tx(TransactionType::Deposit, amount, "Deposit transaction", 
                         now, "Completed", currentUsername);
    repository.addTransaction(tx);
    std::cout << "Deposited " << amount << " EGP successfully!\n";
}

void TransactionService::withdraw(double amount) {
    if (getBalance() >= amount) {
        std::time_t now = std::time(nullptr);
        TransactionDetails tx(TransactionType::Withdrawal, amount, "Withdrawal transaction", 
                             now, "Completed", currentUsername);
        repository.addTransaction(tx);
        std::cout << "Withdrew " << amount << " EGP successfully!\n";
    } else {
        std::cout << "Insufficient balance!\n";
    }
}

void TransactionService::payBill(double amount, const std::string& billType) {
    if (getBalance() >= amount) {
        std::time_t now = std::time(nullptr);
        TransactionDetails tx(TransactionType::BillPayment, amount, billType + " bill payment", 
                             now, "Completed", currentUsername);
        repository.addTransaction(tx);
        std::cout << "Paid " << amount << " EGP for " << billType << " bill successfully!\n";
    } else {
        std::cout << "Insufficient balance!\n";
    }
}

bool TransactionService::transferMoney(double amount, const std::string& recipientUsername) {
    if (!userRepository) {
        std::cout << "Transfer service not available!\n";
        return false;
    }
    
    if (recipientUsername == currentUsername) {
        std::cout << "Cannot transfer money to yourself!\n";
        return false;
    }
    
    // Check if recipient exists
    std::unique_ptr<User> recipient(userRepository->findByUsername(recipientUsername));
    if (!recipient) {
        std::cout << "Recipient user '" << recipientUsername << "' not found!\n";
        return false;
    }
    
    if (getBalance() < amount) {
        std::cout << "Insufficient balance for transfer!\n";
        return false;
    }
    
    std::time_t now = std::time(nullptr);
    
    // Create outgoing transfer transaction for sender
    TransactionDetails senderTx(TransactionType::Transfer, amount, 
                               "Transfer to " + recipientUsername, 
                               now, "Completed", currentUsername);
    repository.addTransaction(senderTx);
    
    // Create incoming transfer transaction for recipient  
    TransactionDetails recipientTx(TransactionType::Transfer, -amount, // Negative amount for recipient (incoming)
                                  "Transfer from " + currentUsername,
                                  now, "Completed", recipientUsername);
    repository.addTransaction(recipientTx);
    
    std::cout << "Successfully transferred " << amount << " EGP to " << recipientUsername << "!\n";
    return true;
}

double TransactionService::getBalance() const {
    double bal = 0.0;
    auto transactions = getUserTransactions();
    
    for (const auto& tx : transactions) {
        if (tx.getType() == TransactionType::Deposit) {
            bal += tx.getAmount();
        } else if (tx.getType() == TransactionType::Withdrawal || 
                   tx.getType() == TransactionType::BillPayment) {
            bal -= tx.getAmount();
        } else if (tx.getType() == TransactionType::Transfer) {
            // For transfers, positive amount = outgoing, negative amount = incoming
            bal -= tx.getAmount();
        }
    }
    return bal;
}

size_t TransactionService::getNumTransactions() const {
    return getUserTransactions().size();
}