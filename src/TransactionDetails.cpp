#include "TransactionDetails.h"
#include <sstream>

TransactionDetails::TransactionDetails(const std::string& t, double a, const std::string& d, std::time_t ts, const std::string& s)
    : type(t), amount(a), description(d), timestamp(ts), status(s) {}

std::string TransactionDetails::getDetails() const {
    std::stringstream ss;
    ss << type << "," << amount << "," << description << "," << timestamp << "," << status;
    return ss.str();
}