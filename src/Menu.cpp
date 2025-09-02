#include "Menu.h"
#include "MenuManager.h"
#include "User.h"
#include "TransactionService.h"
#include "Localizer.h"
#include <limits>
#include <cstdlib>

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char showConfirmBackMain(const std::string& actionName, MenuManager& menuManager) {
    std::cout << "\nYou selected: " << actionName << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << menuManager.getLocalizer().get("confirm") << '\n';
    std::cout << menuManager.getLocalizer().get("back_option") << '\n';
    std::cout << menuManager.getLocalizer().get("main_menu") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Option: ";
    char c; std::cin >> c;
    return c;
}

LanguageSelectionMenu::LanguageSelectionMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult LanguageSelectionMenu::Display() {
    system("clear");
    std::cout << "\n\n=====================================================\n";
    std::cout << " Select Your Language \n";
    std::cout << "=====================================================\n";
    std::cout << "(1) English\n";
    std::cout << "(2) Deutsch\n";
    std::cout << "(Q) Quit\n";
    std::cout << "Option: ";
    std::string choice; std::cin >> choice;

    if (choice == "1") {
        m_menuManager.getSettings().setLanguage("English");
        m_menuManager.ChangeMenu(new WelcomeMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (choice == "2") {
        m_menuManager.getSettings().setLanguage("Deutsch");
        m_menuManager.ChangeMenu(new WelcomeMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (choice == "Q" || choice == "q") {
        return MenuResult::Exit;
    }

    std::cout << "Invalid option!\n";
    return MenuResult::Continue;
}

WelcomeMenu::WelcomeMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult WelcomeMenu::Display() {
    system("clear");
    std::cout << "\n\n=====================================================\n";
    std::cout << " " << m_menuManager.getLocalizer().get("welcome_title") << " \n";
    std::cout << "=====================================================\n";
    std::cout << m_menuManager.getLocalizer().get("login_option") << '\n';
    std::cout << m_menuManager.getLocalizer().get("register_option") << '\n'; // Added
    std::cout << m_menuManager.getLocalizer().get("quit_option") << '\n';
    std::cout << "Option: ";
    char ch; std::cin >> ch;
    switch (ch) {
    case 'L': case 'l':
        m_menuManager.ChangeMenu(new LoginMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    case 'R': case 'r': // Added
        m_menuManager.ChangeMenu(new RegistrationMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    case 'Q': case 'q':
        return MenuResult::Exit;
    default:
        std::cout << m_menuManager.getLocalizer().get("invalid_option") << '\n';
        return MenuResult::Continue;
    }
}

RegistrationMenu::RegistrationMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult RegistrationMenu::Display() {
    system("clear");
    std::string uname, pass;
    std::cout << m_menuManager.getLocalizer().get("enter_new_username");
    std::cin >> uname;
    std::cout << m_menuManager.getLocalizer().get("enter_new_password");
    std::cin >> pass;

    AuthenticationService& auth = m_menuManager.getAuthService();
    UserRepository* repo = auth.getRepo();

    if (repo->findByUsername(uname) != nullptr) {
        std::cout << "\n" << m_menuManager.getLocalizer().get("username_taken") << '\n';
    } else {
        User newUser(uname, pass);
        repo->save(newUser);
        std::cout << "\n" << m_menuManager.getLocalizer().get("registration_success") << '\n';
        m_menuManager.login(uname);
        m_menuManager.ChangeMenu(new OptionsMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    }

    std::cout << "++++++++++++++++++++++\n";
    std::cout << m_menuManager.getLocalizer().get("retry_option") << '\n';
    std::cout << m_menuManager.getLocalizer().get("back_option") << '\n';
    std::cout << "++++++++++++++++++++++\n";
    std::cout << "Option: ";
    char ch; std::cin >> ch;
    if (ch == 'R' || ch == 'r') return MenuResult::Continue;
    if (ch == 'B' || ch == 'b') {
        m_menuManager.ChangeMenu(new WelcomeMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    }
    return MenuResult::Continue;
}


LoginMenu::LoginMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult LoginMenu::Display() {
    system("clear");
    std::string uname, pass;
    std::cout << m_menuManager.getLocalizer().get("enter_username");
    std::cin >> uname;
    std::cout << m_menuManager.getLocalizer().get("enter_password");
    std::cin >> pass;

    if (m_menuManager.getAuthService().login(uname, pass)) {
        std::cout << "\n" << m_menuManager.getLocalizer().get("login_success") << '\n';
        m_menuManager.login(uname);
        m_menuManager.ChangeMenu(new OptionsMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    }

    std::cout << "\n" << m_menuManager.getLocalizer().get("invalid_credentials") << '\n';
    std::cout << "++++++++++++++++++++++\n";
    std::cout << m_menuManager.getLocalizer().get("retry_option") << '\n';
    std::cout << m_menuManager.getLocalizer().get("quit_option") << '\n';
    std::cout << "++++++++++++++++++++++\n";
    std::cout << "Option: ";
    char ch; std::cin >> ch;
    if (ch == 'R' || ch == 'r') return MenuResult::Continue;
    if (ch == 'Q' || ch == 'q') return MenuResult::Exit;
    return MenuResult::Continue;
}

OptionsMenu::OptionsMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult OptionsMenu::Display() {
    std::cout << "\n" << m_menuManager.getLocalizer().get("options_title") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << m_menuManager.getLocalizer().get("account_statement") << '\n';
    std::cout << m_menuManager.getLocalizer().get("check_balance") << '\n';
    std::cout << m_menuManager.getLocalizer().get("transactions_option") << '\n';
    std::cout << m_menuManager.getLocalizer().get("logout_option") << '\n';
    std::cout << m_menuManager.getLocalizer().get("quit_option") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Service No.: ";
    std::string choice; std::cin >> choice;

    TransactionService& txService = m_menuManager.getTransactionService();
    User& user = m_menuManager.getUser();

    if (choice == "1") {
        char sub = showConfirmBackMain(m_menuManager.getLocalizer().get("account_statement").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            std::cout << "Account Holder: " << user.getUsername() << '\n';
            txService.showBalance();
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "2") {
        char sub = showConfirmBackMain(m_menuManager.getLocalizer().get("check_balance").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            txService.showBalance();
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "3") {
        char sub = showConfirmBackMain(m_menuManager.getLocalizer().get("transactions_option").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            m_menuManager.ChangeMenu(new TransactionMenu(m_menuManager));
            return MenuResult::ClearAndContinue;
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "4") {
        m_menuManager.logout();
        m_menuManager.ChangeMenu(new WelcomeMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    }
    if (choice == "Q" || choice == "q") {
        return MenuResult::Exit;
    }

    std::cout << m_menuManager.getLocalizer().get("invalid_option") << '\n';
    return MenuResult::Continue;
}

TransactionMenu::TransactionMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult TransactionMenu::Display() {
    system("clear");
    std::cout << "\n" << m_menuManager.getLocalizer().get("transaction_title") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << m_menuManager.getLocalizer().get("show_history") << '\n';
    std::cout << m_menuManager.getLocalizer().get("deposit_option") << '\n';
    std::cout << m_menuManager.getLocalizer().get("withdraw_option") << '\n';
    std::cout << m_menuManager.getLocalizer().get("pay_bills") << '\n';
    std::cout << m_menuManager.getLocalizer().get("back_option") << '\n';
    std::cout << m_menuManager.getLocalizer().get("quit_option") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Option: ";
    std::string choice; std::cin >> choice;

    TransactionService& txService = m_menuManager.getTransactionService();
    User& user = m_menuManager.getUser();

    if (choice == "1") {
        char sub = showConfirmBackMain(m_menuManager.getLocalizer().get("show_history").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            txService.showTransactions();
            if (txService.getNumTransactions() > 0) {
                std::cout << m_menuManager.getLocalizer().get("transaction_details_prompt");
                char yn; std::cin >> yn;
                if (yn == 'Y' || yn == 'y' || yn == 'J' || yn == 'j') {
                    std::cout << m_menuManager.getLocalizer().get("transaction_number_prompt") << txService.getNumTransactions() << "): ";
                    size_t num;
                    if (!(std::cin >> num)) {
                        clearInput();
                        std::cout << m_menuManager.getLocalizer().get("invalid_number");
                        return MenuResult::Continue;
                    }
                    if (num < 1 || num > txService.getNumTransactions()) {
                        std::cout << m_menuManager.getLocalizer().get("invalid_transaction");
                        return MenuResult::Continue;
                    }
                    txService.showTransactionDetails(num - 1, user.getUsername());
                }
            }
        } else if (sub == 'M' || sub == 'm' || sub == 'B' || sub == 'b') {
            m_menuManager.ChangeMenu(new OptionsMenu(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "2") {
        char sub = showConfirmBackMain(m_menuManager.getLocalizer().get("deposit_option").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            double amt;
            std::cout << m_menuManager.getLocalizer().get("amount_prompt") << m_menuManager.getLocalizer().get("deposit_option").substr(4) << ": ";
            if (!(std::cin >> amt)) { clearInput(); std::cout << m_menuManager.getLocalizer().get("invalid_number"); return MenuResult::Continue; }
            txService.deposit(amt);
        } else if (sub == 'M' || sub == 'm' || sub == 'B' || sub == 'b') {
            m_menuManager.ChangeMenu(new OptionsMenu(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "3") {
        char sub = showConfirmBackMain(m_menuManager.getLocalizer().get("withdraw_option").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            double amt;
            std::cout << m_menuManager.getLocalizer().get("amount_prompt") << m_menuManager.getLocalizer().get("withdraw_option").substr(4) << ": ";
            if (!(std::cin >> amt)) { clearInput(); std::cout << m_menuManager.getLocalizer().get("invalid_number"); return MenuResult::Continue; }
            txService.withdraw(amt);
        } else if (sub == 'M' || sub == 'm' || sub == 'B' || sub == 'b') {
            m_menuManager.ChangeMenu(new OptionsMenu(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "4") {
        char sub = showConfirmBackMain(m_menuManager.getLocalizer().get("pay_bills").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            m_menuManager.ChangeMenu(new PayBillsMenu(m_menuManager));
            return MenuResult::ClearAndContinue;
        } else if (sub == 'M' || sub == 'm' || sub == 'B' || sub == 'b') {
            m_menuManager.ChangeMenu(new OptionsMenu(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "B" || choice == "b") {
        m_menuManager.ChangeMenu(new OptionsMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    }
    if (choice == "Q" || choice == "q") {
        return MenuResult::Exit;
    }

    std::cout << m_menuManager.getLocalizer().get("invalid_option") << '\n';
    return MenuResult::Continue;
}

PayBillsMenu::PayBillsMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult PayBillsMenu::Display() {
    system("clear");
    std::cout << "\n" << m_menuManager.getLocalizer().get("pay_bills_title") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << m_menuManager.getLocalizer().get("electricity") << '\n';
    std::cout << m_menuManager.getLocalizer().get("water") << '\n';
    std::cout << m_menuManager.getLocalizer().get("gas") << '\n';
    std::cout << m_menuManager.getLocalizer().get("back_option") << '\n';
    std::cout << m_menuManager.getLocalizer().get("quit_option") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Option: ";
    std::string choice; std::cin >> choice;

    if (choice == "1" || choice == "2" || choice == "3") {
        std::string billType;
        if (choice == "1") billType = m_menuManager.getLocalizer().get("electricity").substr(4);
        else if (choice == "2") billType = m_menuManager.getLocalizer().get("water").substr(4);
        else billType = m_menuManager.getLocalizer().get("gas").substr(4);

        char sub = showConfirmBackMain(m_menuManager.getLocalizer().get("pay_bills").substr(4) + " " + billType, m_menuManager);
        if (sub == 'C' || sub == 'c') {
            double amt;
            std::cout << m_menuManager.getLocalizer().get("bill_amount") << billType << m_menuManager.getLocalizer().get("bill_amount_suffix");
            if (!(std::cin >> amt)) { 
                clearInput(); 
                std::cout << m_menuManager.getLocalizer().get("invalid_number"); 
                return MenuResult::Continue; 
            }
            m_menuManager.getTransactionService().payBill(amt, billType);
        } else if (sub == 'B' || sub == 'b' || sub == 'M' || sub == 'm') {
            m_menuManager.ChangeMenu(new TransactionMenu(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    }
    if (choice == "B" || choice == "b") {
        m_menuManager.ChangeMenu(new TransactionMenu(m_menuManager));
        return MenuResult::ClearAndContinue;
    }
    if (choice == "Q" || choice == "q") {
        return MenuResult::Exit;
    }

    std::cout << m_menuManager.getLocalizer().get("invalid_option") << '\n';
    return MenuResult::Continue;
}