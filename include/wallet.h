#pragma once

#include <iostream>
#include <vector>
#include <string>

class User {
private:
    std::string username;
    std::string password;

public:
    User(std::string uname = "admin", std::string pass = "admin");
    bool login(const std::string &input_username, const std::string &input_pass);
    std::string getUsername() const;
};

class Wallet {
private:
    double balance;
    std::vector<std::string> transactions;

public:
    Wallet();
    void deposit(double amount);
    void withdraw(double amount);
    void showBalance() const;
    void showTransactions() const;
};