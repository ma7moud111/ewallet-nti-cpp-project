#include "MenuManager.h"
#include "Menu.h"
#include "ApplicationResources.h"
#include "TransactionService.h"
#include "User.h"
#include <functional>
#include <stdexcept>

MenuManager::MenuManager(ApplicationResources& res)
    : currentMenu(std::make_unique<LanguageSelectionMenu>(*this))
    , resources(res) {
}

MenuManager::~MenuManager() = default;

void MenuManager::ChangeMenu(std::unique_ptr<Menu> newMenu) {
    currentMenu = std::move(newMenu);
}

void MenuManager::Run() {
    while (currentMenu != nullptr) {
        MenuResult result = currentMenu->Display();
        if (result == MenuResult::Exit) {
            break;
        } else if (result == MenuResult::ClearAndContinue) {
            system("clear");
        }
    }
}

void MenuManager::login(const std::string& username) {
    currentUser = std::make_unique<User>(username, "");
    txService = std::make_unique<TransactionService>(
        resources.getTransactionRepository(), 
        username, 
        &resources.getUserRepository()
    );
}

void MenuManager::logout() {
    currentUser.reset();
    txService.reset();
}

User& MenuManager::getUser() {
    if (!currentUser) {
        throw std::runtime_error("No user logged in");
    }
    return *currentUser;
}

TransactionService& MenuManager::getTransactionService() {
    if (!txService) {
        throw std::runtime_error("Transaction service not initialized (not logged in)");
    }
    return *txService;
}

bool MenuManager::isLoggedIn() const {
    return currentUser != nullptr;
}