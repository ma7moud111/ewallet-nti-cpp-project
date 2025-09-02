#pragma once
#include <string>
#include <iostream>

class MenuManager;

enum class MenuResult { Continue, ClearAndContinue, Exit };

class Menu {
protected:
    MenuManager& m_menuManager;
public:
    explicit Menu(MenuManager& menuManager) : m_menuManager(menuManager) {}
    virtual ~Menu() = default;
    virtual MenuResult Display() = 0;
};

class LanguageSelectionMenu : public Menu {
public:
    explicit LanguageSelectionMenu(MenuManager& menuManager);
    MenuResult Display() override;
};

class WelcomeMenu : public Menu {
public:
    explicit WelcomeMenu(MenuManager& menuManager);
    MenuResult Display() override;
};

class LoginMenu : public Menu {
public:
    explicit LoginMenu(MenuManager& menuManager);
    MenuResult Display() override;
};

class RegistrationMenu : public Menu { // Added
public:
    explicit RegistrationMenu(MenuManager& menuManager);
    MenuResult Display() override;
};

class OptionsMenu : public Menu {
public:
    explicit OptionsMenu(MenuManager& menuManager);
    MenuResult Display() override;
};

class TransactionMenu : public Menu {
public:
    explicit TransactionMenu(MenuManager& menuManager);
    MenuResult Display() override;
};

class PayBillsMenu : public Menu {
public:
    explicit PayBillsMenu(MenuManager& menuManager);
    MenuResult Display() override;
};

char showConfirmBackMain(const std::string& actionName, MenuManager& menuManager);