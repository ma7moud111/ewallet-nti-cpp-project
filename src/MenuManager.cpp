#include "MenuManager.h"
#include "Menu.h"
#include "Localizer.h"
#include "TransactionInMemoryRepository.h"
#include "TransactionFileSystemRepository.h"
#include "TransactionService.h"
#include <functional>
#include <stdexcept>

MenuManager::MenuManager(AuthenticationService& as, Settings& s) 
    : currentMenu(new LanguageSelectionMenu(*this)), authService(as), settings(s),
      localizer(std::make_unique<Localizer>(s)) {
    if (!localizer) {
        throw std::runtime_error("Failed to initialize Localizer");
    }
    // txRepo and txService initialized in login
}

MenuManager::~MenuManager() {
    delete currentMenu;
}

void MenuManager::ChangeMenu(Menu* newMenu) {
    delete currentMenu;
    currentMenu = newMenu;
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

void MenuManager::login(const std::string& uname) {
    currentUser = std::make_unique<User>(uname, "");
    // Initialize per-user txRepo
    std::string repoType = settings.txRepoType;
    if (repoType == "InMemory") {
        txRepo = std::make_unique<TransactionInMemoryRepository>();
    } else {
        txRepo = std::make_unique<TransactionFileSystemRepository>(uname + "_transactions.txt");
    }
    txService = std::make_unique<TransactionService>(*txRepo);
}

void MenuManager::logout() {
    currentUser.reset();
    txRepo.reset();
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

AuthenticationService& MenuManager::getAuthService() {
    return authService;
}

bool MenuManager::isLoggedIn() const {
    return currentUser != nullptr;
}

Localizer& MenuManager::getLocalizer() {
    return *localizer;
}