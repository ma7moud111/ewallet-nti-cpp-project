#pragma once
#include "Menu.h"
#include "AuthenticationService.h"
#include "Settings.h"
#include "User.h"
#include "TransactionRepository.h"
#include "TransactionService.h"
#include "Localizer.h"
#include <memory>

class MenuManager {
private:
    Menu* currentMenu;
    AuthenticationService& authService;
    Settings& settings;
    std::unique_ptr<User> currentUser;
    std::unique_ptr<TransactionRepository> txRepo;
    std::unique_ptr<TransactionService> txService;
    std::unique_ptr<Localizer> localizer;

public:
    MenuManager(AuthenticationService& as, Settings& s);
    ~MenuManager();
    void ChangeMenu(Menu* newMenu);
    void Run();
    void login(const std::string& uname);
    void logout();
    User& getUser();
    TransactionService& getTransactionService();
    AuthenticationService& getAuthService();
    bool isLoggedIn() const;
    Localizer& getLocalizer();
    Settings& getSettings() { return settings; }
};