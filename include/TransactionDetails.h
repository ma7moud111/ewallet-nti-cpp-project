#ifndef TRANSACTION_DETAILS_H
#define TRANSACTION_DETAILS_H

#include <string>
#include <ctime>

class TransactionDetails {
private:
    std::string type;
    double amount;
    std::string description;
    std::time_t timestamp;
    std::string status;

public:
    TransactionDetails(const std::string& t, double a, const std::string& d, std::time_t ts, const std::string& s);
    std::string getDetails() const;
    const std::string& getType() const { return type; }
    double getAmount() const { return amount; }
    const std::time_t& getTimestamp() const { return timestamp; }
    const std::string& getStatus() const { return status; }
    const std::string& getDescription() const { return description; }
};

#endif