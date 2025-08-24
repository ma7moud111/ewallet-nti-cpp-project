#pragma once
#include "menu.h"
#include "user.h"
#include "wallet.h"

class Menu; 

class MenuManager {
private:
    Menu* m_currentMenu;
    User m_user;
    Wallet m_wallet;
public:
    MenuManager();
    explicit MenuManager(Menu* firstMenu);
    ~MenuManager();

    void ChangeMenu(Menu* newMenu);
    void Run();

    User& getUser() { return m_user; }
    Wallet& getWallet() { return m_wallet; }
};
