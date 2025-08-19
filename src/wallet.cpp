#include "wallet.h"


// -------------------- User --------------------
User::User(std::string uname, std::string pass)
{
    username = uname; 
    password = pass;
}

bool User::login(const std::string &input_username, const std::string &input_pass) {
    return (input_username == username && input_pass == password);
}

std::string User::getUsername() const 
{
    return username;
}

// -------------------- Wallet --------------------
Wallet::Wallet()  
{
    balance = 0.0;
}

void Wallet::deposit(double amount) 
{
    balance += amount;
    transactions.push_back("Deposited: " + std::to_string(amount));
}

void Wallet::withdraw(double amount) 
{
    if (amount > balance) {
        std::cout << "Insufficient funds!\n";
        return;
    }
    balance -= amount;
    transactions.push_back("Withdrew: " + std::to_string(amount));
}

void Wallet::showBalance() const 
{
    std::cout << "Current Balance: " << balance << " EGP\n";
}

void Wallet::showTransactions() const 
{
    if (transactions.empty()) {
        std::cout << "No transactions yet.\n";
        return;
    }
    std::cout << "Transaction History:\n";
    for (auto &t : transactions)
        std::cout << "- " << t << std::endl;
}
