#include "menu.h"
#include "menu_manager.h"
#include "user.h"
#include "wallet.h"
#include <limits>


static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char showConfirmBackMain(const std::string& actionName) {
    std::cout << "\nYou selected: " << actionName << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "(C) Confirm\n";
    std::cout << "(B) Back\n";
    std::cout << "(M) Back to Main Menu\n";
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Option: ";
    char c; std::cin >> c;
    return c;
}


WelcomeMenu::WelcomeMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult WelcomeMenu::Display() {
    system("clear");
    std::cout << "\n\n=====================================================\n";
    std::cout << "             Welcome to NTI Smart Wallet             \n";
    std::cout << "=====================================================\n";
    std::cout << "(L) Login\n";
    std::cout << "(Q) Quit\n";
    std::cout << "Option: ";
    char ch; std::cin >> ch;
    switch (ch) {
        case 'L': case 'l':
            m_menuManager.ChangeMenu(new LoginMenu(m_menuManager));
            return MenuResult::ClearAndContinue;
        case 'Q': case 'q':
            return MenuResult::Exit;
        default:
            std::cout << "Invalid option.\n";
            return MenuResult::Continue;
    }
}

LoginMenu::LoginMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult LoginMenu::Display() {
    system("clear");
    std::string uname, pass;
    std::cout << "Please enter your username: ";
    std::cin >> uname;
    std::cout << "Please enter your password: ";
    std::cin >> pass;

    if (m_menuManager.getUser().login(uname, pass)) {
        std::cout << "\nLogged in Successfully!\n";
        m_menuManager.ChangeMenu(new OptionsMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    }

    std::cout << "\nInvalid credentials!\n";
    std::cout << "++++++++++++++++++++++\n";
    std::cout << "(R) Retry\n";
    std::cout << "(Q) Quit\n";
    std::cout << "++++++++++++++++++++++\n";
    std::cout << "Option: ";
    char ch; std::cin >> ch;
    if (ch == 'Q' || ch == 'q') return MenuResult::Exit;
    // else retry login
    return MenuResult::Continue;
}


OptionsMenu::OptionsMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult OptionsMenu::Display() {
    std::cout << "\nPlease choose a service:\n";
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "(1) Check Account Statement\n";
    std::cout << "(2) Check Balance\n";
    std::cout << "(3) Show Transaction History\n";
    std::cout << "(4) Withdraw\n";
    std::cout << "(5) Deposit\n";
    std::cout << "(6) Logout\n";
    std::cout << "(Q) Quit\n";
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Service No.: ";
    std::string choice; std::cin >> choice;

    Wallet& wallet = m_menuManager.getWallet();
    User& user = m_menuManager.getUser();

    if (choice == "1") {
        char sub = showConfirmBackMain("Check Account Statement");
        if (sub == 'C' || sub == 'c') {
            std::cout << "Account Holder: " << user.getUsername() << '\n';
            wallet.showBalance();
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "2") {
        char sub = showConfirmBackMain("Check Balance");
        if (sub == 'C' || sub == 'c') {
            wallet.showBalance();
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "3") {
        char sub = showConfirmBackMain("Show Transaction History");
        if (sub == 'C' || sub == 'c') {
            wallet.showTransactions();
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "4") {
        char sub = showConfirmBackMain("Withdraw");
        if (sub == 'C' || sub == 'c') {
            double amt;
            std::cout << "Enter amount to withdraw: ";
            if (!(std::cin >> amt)) { clearInput(); std::cout << "Invalid number.\n"; return MenuResult::Continue; }
            wallet.withdraw(amt);
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "5") {
        char sub = showConfirmBackMain("Deposit");
        if (sub == 'C' || sub == 'c') {
            double amt;
            std::cout << "Enter amount to deposit: ";
            if (!(std::cin >> amt)) { clearInput(); std::cout << "Invalid number.\n"; return MenuResult::Continue; }
            wallet.deposit(amt);
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "6") {
        m_menuManager.ChangeMenu(new WelcomeMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    }
    if (choice == "Q" || choice == "q") {
        return MenuResult::Exit;
    }

    std::cout << "Invalid option!\n";
    return MenuResult::Continue;
}
