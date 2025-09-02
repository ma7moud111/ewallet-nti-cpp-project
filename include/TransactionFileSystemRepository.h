#pragma once
#include "TransactionRepository.h"
#include <string>
#include <vector>

class TransactionFileSystemRepository : public TransactionRepository {
public:
    explicit TransactionFileSystemRepository(const std::string& filename);
    void addTransaction(const TransactionDetails& tx) override;
    std::vector<TransactionDetails> getAllTransactions() const override;

private:
    std::string filename;
};