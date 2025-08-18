#pragma once
#include <string>

class SmartWallet
{
    public:
    SmartWallet();
    void setUserData(std::string un, std::string pass);

    
    private:
    std::string username;
    std::string password;
    float balance;
    float withdrawalAmount;
    float depositeAmount;
    int transactionsNo;
};