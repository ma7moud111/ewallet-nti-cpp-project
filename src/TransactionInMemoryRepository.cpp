#include "TransactionInMemoryRepository.h"

void TransactionInMemoryRepository::addTransaction(const TransactionDetails& tx) {
    transactions.push_back(tx);
}

std::vector<TransactionDetails> TransactionInMemoryRepository::getAllTransactions() const {
    return transactions;
}