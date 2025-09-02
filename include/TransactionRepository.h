#pragma once
#include "TransactionDetails.h"
#include <string>
#include <vector>

class TransactionRepository {
public:
    virtual ~TransactionRepository() = default;
    virtual void addTransaction(const TransactionDetails& tx) = 0;
    virtual std::vector<TransactionDetails> getAllTransactions() const = 0;
};