#include "TransactionFileSystemRepository.h"
#include "TransactionDetails.h"
#include <fstream>
#include <sstream>

TransactionFileSystemRepository::TransactionFileSystemRepository(const std::string& filename) : filename(filename) {}

void TransactionFileSystemRepository::addTransaction(const TransactionDetails& tx) {
    std::ofstream file(filename, std::ios::app);
    if (file) {
        file << tx.getDetails() << "\n";
    }
}

std::vector<TransactionDetails> TransactionFileSystemRepository::getAllTransactions() const {
    std::vector<TransactionDetails> transactions;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() == 5) {
            std::string type = tokens[0];
            double amount = std::stod(tokens[1]);
            std::string description = tokens[2];
            std::time_t timestamp = static_cast<std::time_t>(std::stol(tokens[3]));
            std::string status = tokens[4];
            transactions.emplace_back(type, amount, description, timestamp, status);
        }
    }
    return transactions;
}