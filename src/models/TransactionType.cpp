#include "TransactionType.h"
#include <stdexcept>

const char* transactionTypeToString(TransactionType type) {
    switch (type) {
        case TransactionType::Deposit: return "Deposit";
        case TransactionType::Withdrawal: return "Withdrawal";
        case TransactionType::BillPayment: return "Bill Payment";
        case TransactionType::Transfer: return "Transfer";
    }
    return "Unknown";
}

TransactionType stringToTransactionType(const std::string& str) {
    if (str == "Deposit") return TransactionType::Deposit;
    if (str == "Withdrawal") return TransactionType::Withdrawal;
    if (str == "Bill Payment") return TransactionType::BillPayment;
    if (str == "Transfer") return TransactionType::Transfer;
    throw std::invalid_argument("Invalid transaction type: " + str);
}