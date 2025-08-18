#include "wallet.h"

SmartWallet::SmartWallet()
{
    username = "";
    password = "";
}

void SmartWallet::setUserData(std::string un, std::string pass)
{
    username = un;
    password = pass;
}

