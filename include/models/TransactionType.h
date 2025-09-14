#pragma once
#include <string>

enum class TransactionType {
    Deposit,
    Withdrawal,
    BillPayment,
    Transfer
};

const char* transactionTypeToString(TransactionType type);
TransactionType stringToTransactionType(const std::string& str);