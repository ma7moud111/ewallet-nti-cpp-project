#include "Menu.h"
#include "MenuManager.h"
#include "ApplicationResources.h"
#include "User.h"
#include "TransactionService.h"
#include "TransactionType.h"
#include "Localizer.h"
#include "UserRepository.h"
#include <limits>
#include <cstdlib>

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char showConfirmBackMain(const std::string& actionName, MenuManager& menuManager) {
    auto& localizer = menuManager.getResources().getLocalizer();
    
    std::cout << "\nYou selected: " << actionName << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << localizer.get("confirm") << '\n';
    std::cout << localizer.get("back_option") << '\n';
    std::cout << localizer.get("main_menu") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Option: ";
    char c; 
    std::cin >> c;
    return c;
}

// LanguageSelectionMenu Implementation
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
    
    std::string choice; 
    std::cin >> choice;
    
    if (choice == "1") {
        m_menuManager.getResources().getSettings().setLanguage("English");
        m_menuManager.ChangeMenu(std::make_unique<WelcomeMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (choice == "2") {
        m_menuManager.getResources().getSettings().setLanguage("Deutsch");
        m_menuManager.ChangeMenu(std::make_unique<WelcomeMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (choice == "Q" || choice == "q") {
        return MenuResult::Exit;
    } else {
        std::cout << "Invalid option!\n";
        return MenuResult::Continue;
    }
}

// WelcomeMenu Implementation
WelcomeMenu::WelcomeMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult WelcomeMenu::Display() {
    system("clear");
    auto& localizer = m_menuManager.getResources().getLocalizer();
    
    std::cout << "\n\n=====================================================\n";
    std::cout << " " << localizer.get("welcome_title") << " \n";
    std::cout << "=====================================================\n";
    std::cout << localizer.get("login_option") << '\n';
    std::cout << localizer.get("register_option") << '\n';
    std::cout << localizer.get("quit_option") << '\n';
    std::cout << "Option: ";
    
    char ch; 
    std::cin >> ch;
    
    if (ch == 'L' || ch == 'l') {
        m_menuManager.ChangeMenu(std::make_unique<LoginMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (ch == 'R' || ch == 'r') {
        m_menuManager.ChangeMenu(std::make_unique<RegistrationMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (ch == 'Q' || ch == 'q') {
        return MenuResult::Exit;
    } else {
        std::cout << localizer.get("invalid_option") << '\n';
        return MenuResult::Continue;
    }
}

// RegistrationMenu Implementation
RegistrationMenu::RegistrationMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult RegistrationMenu::Display() {
    system("clear");
    auto& resources = m_menuManager.getResources();
    auto& localizer = resources.getLocalizer();
    auto& userRepo = resources.getUserRepository();
    
    std::string uname, pass;
    std::cout << localizer.get("enter_new_username");
    std::cin >> uname;
    std::cout << localizer.get("enter_new_password");
    std::cin >> pass;
    
    std::unique_ptr<User> existingUser(userRepo.findByUsername(uname));
    if (existingUser) {
        std::cout << "\n" << localizer.get("username_taken") << '\n';
    } else {
        User newUser(uname, pass);
        userRepo.save(newUser);
        std::cout << "\n" << localizer.get("registration_success") << '\n';
        m_menuManager.login(uname);
        m_menuManager.ChangeMenu(std::make_unique<OptionsMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    }
    
    std::cout << "++++++++++++++++++++++\n";
    std::cout << localizer.get("retry_option") << '\n';
    std::cout << localizer.get("back_option") << '\n';
    std::cout << "++++++++++++++++++++++\n";
    std::cout << "Option: ";
    
    char ch; 
    std::cin >> ch;
    
    if (ch == 'R' || ch == 'r') {
        return MenuResult::Continue;
    } else if (ch == 'B' || ch == 'b') {
        m_menuManager.ChangeMenu(std::make_unique<WelcomeMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else {
        return MenuResult::Continue;
    }
}

// LoginMenu Implementation
LoginMenu::LoginMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult LoginMenu::Display() {
    system("clear");
    auto& resources = m_menuManager.getResources();
    auto& localizer = resources.getLocalizer();
    auto& userRepo = resources.getUserRepository();
    
    std::string uname, pass;
    std::cout << localizer.get("enter_username");
    std::cin >> uname;
    std::cout << localizer.get("enter_password");
    std::cin >> pass;
    
    if (userRepo.authenticate(uname, pass)) {
        std::cout << "\n" << localizer.get("login_success") << '\n';
        m_menuManager.login(uname);
        m_menuManager.ChangeMenu(std::make_unique<OptionsMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else {
        std::cout << "\n" << localizer.get("invalid_credentials") << '\n';
        std::cout << "++++++++++++++++++++++\n";
        std::cout << localizer.get("retry_option") << '\n';
        std::cout << localizer.get("quit_option") << '\n';
        std::cout << "++++++++++++++++++++++\n";
        std::cout << "Option: ";
        
        char ch; 
        std::cin >> ch;
        
        if (ch == 'R' || ch == 'r') {
            return MenuResult::Continue;
        } else if (ch == 'Q' || ch == 'q') {
            return MenuResult::Exit;
        } else {
            return MenuResult::Continue;
        }
    }
}

// OptionsMenu Implementation
OptionsMenu::OptionsMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult OptionsMenu::Display() {
    auto& localizer = m_menuManager.getResources().getLocalizer();
    auto& txService = m_menuManager.getTransactionService();
    auto& user = m_menuManager.getUser();
    
    std::cout << "\n" << localizer.get("options_title") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << localizer.get("account_statement") << '\n';
    std::cout << localizer.get("check_balance") << '\n';
    std::cout << localizer.get("transactions_option") << '\n';
    std::cout << localizer.get("logout_option") << '\n';
    std::cout << localizer.get("quit_option") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Service No.: ";
    
    std::string choice; 
    std::cin >> choice;
    
    if (choice == "1") {
        char sub = showConfirmBackMain(localizer.get("account_statement").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            std::cout << "Account Holder: " << user.getUsername() << '\n';
            txService.showBalance();
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    } else if (choice == "2") {
        char sub = showConfirmBackMain(localizer.get("check_balance").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            txService.showBalance();
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    } else if (choice == "3") {
        char sub = showConfirmBackMain(localizer.get("transactions_option").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            m_menuManager.ChangeMenu(std::make_unique<TransactionMenu>(m_menuManager));
            return MenuResult::ClearAndContinue;
        } else if (sub == 'M' || sub == 'm') {
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    } else if (choice == "4") {
        m_menuManager.logout();
        m_menuManager.ChangeMenu(std::make_unique<WelcomeMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (choice == "Q" || choice == "q") {
        return MenuResult::Exit;
    } else {
        std::cout << localizer.get("invalid_option") << '\n';
        return MenuResult::Continue;
    }
}

// TransactionMenu Implementation (Updated with Transfer)
TransactionMenu::TransactionMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult TransactionMenu::Display() {
    system("clear");
    auto& localizer = m_menuManager.getResources().getLocalizer();
    auto& txService = m_menuManager.getTransactionService();
    
    std::cout << "\n" << localizer.get("transaction_title") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << localizer.get("show_history") << '\n';
    std::cout << localizer.get("deposit_option") << '\n';
    std::cout << localizer.get("withdraw_option") << '\n';
    std::cout << localizer.get("transfer_option") << '\n';
    std::cout << localizer.get("pay_bills") << '\n';
    std::cout << localizer.get("back_option") << '\n';
    std::cout << localizer.get("quit_option") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Option: ";
    
    std::string choice; 
    std::cin >> choice;
    
    if (choice == "1") {
        char sub = showConfirmBackMain(localizer.get("show_history").substr(4), m_menuManager);
        
        if (sub == 'C' || sub == 'c') {
            txService.showTransactions();
            size_t numTransactions = txService.getNumTransactions();
            
            if (numTransactions > 0) {
                std::cout << localizer.get("transaction_details_prompt");
                char yn; 
                std::cin >> yn;
                
                if (yn == 'Y' || yn == 'y' || yn == 'J' || yn == 'j') {
                    std::cout << localizer.get("transaction_number_prompt") 
                              << numTransactions << "): ";
                    size_t num;
                    
                    if (!(std::cin >> num)) {
                        clearInput();
                        std::cout << localizer.get("invalid_number");
                        return MenuResult::Continue;
                    }
                    
                    if (num < 1 || num > numTransactions) {
                        std::cout << localizer.get("invalid_transaction");
                        return MenuResult::Continue;
                    }
                    
                    m_menuManager.ChangeMenu(std::make_unique<TransactionDetailsMenu>(m_menuManager, num - 1));
                    return MenuResult::ClearAndContinue;
                }
            }
        } else if (sub == 'M' || sub == 'm' || sub == 'B' || sub == 'b') {
            m_menuManager.ChangeMenu(std::make_unique<OptionsMenu>(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    } else if (choice == "2") {
        char sub = showConfirmBackMain(localizer.get("deposit_option").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            double amt;
            std::cout << localizer.get("amount_prompt") << localizer.get("deposit_option").substr(4) << ": ";
            if (!(std::cin >> amt)) { 
                clearInput(); 
                std::cout << localizer.get("invalid_number"); 
                return MenuResult::Continue; 
            }
            txService.deposit(amt);
        } else if (sub == 'M' || sub == 'm' || sub == 'B' || sub == 'b') {
            m_menuManager.ChangeMenu(std::make_unique<OptionsMenu>(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    } else if (choice == "3") {
        char sub = showConfirmBackMain(localizer.get("withdraw_option").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            double amt;
            std::cout << localizer.get("amount_prompt") << localizer.get("withdraw_option").substr(4) << ": ";
            if (!(std::cin >> amt)) { 
                clearInput(); 
                std::cout << localizer.get("invalid_number"); 
                return MenuResult::Continue; 
            }
            txService.withdraw(amt);
        } else if (sub == 'M' || sub == 'm' || sub == 'B' || sub == 'b') {
            m_menuManager.ChangeMenu(std::make_unique<OptionsMenu>(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    } else if (choice == "4") {
        char sub = showConfirmBackMain(localizer.get("transfer_option").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            std::string recipient;
            double amt;
            
            std::cout << localizer.get("enter_recipient");
            std::cin >> recipient;
            
            std::cout << localizer.get("enter_transfer_amount");
            if (!(std::cin >> amt)) {
                clearInput();
                std::cout << localizer.get("invalid_number");
                return MenuResult::Continue;
            }
            
            if (txService.transferMoney(amt, recipient)) {
                std::cout << localizer.get("transfer_success") << '\n';
            } else {
                std::cout << localizer.get("transfer_failed") << '\n';
            }
        } else if (sub == 'M' || sub == 'm' || sub == 'B' || sub == 'b') {
            m_menuManager.ChangeMenu(std::make_unique<OptionsMenu>(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    } else if (choice == "5") {
        char sub = showConfirmBackMain(localizer.get("pay_bills").substr(4), m_menuManager);
        if (sub == 'C' || sub == 'c') {
            m_menuManager.ChangeMenu(std::make_unique<PayBillsMenu>(m_menuManager));
            return MenuResult::ClearAndContinue;
        } else if (sub == 'M' || sub == 'm' || sub == 'B' || sub == 'b') {
            m_menuManager.ChangeMenu(std::make_unique<OptionsMenu>(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    } else if (choice == "B" || choice == "b") {
        m_menuManager.ChangeMenu(std::make_unique<OptionsMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (choice == "Q" || choice == "q") {
        return MenuResult::Exit;
    } else {
        std::cout << localizer.get("invalid_option") << '\n';
        return MenuResult::Continue;
    }
}

// PayBillsMenu Implementation (remains the same)
PayBillsMenu::PayBillsMenu(MenuManager& menuManager) : Menu(menuManager) {}

MenuResult PayBillsMenu::Display() {
    system("clear");
    auto& localizer = m_menuManager.getResources().getLocalizer();
    auto& txService = m_menuManager.getTransactionService();
    
    std::cout << "\n" << localizer.get("pay_bills_title") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << localizer.get("electricity") << '\n';
    std::cout << localizer.get("water") << '\n';
    std::cout << localizer.get("gas") << '\n';
    std::cout << localizer.get("back_option") << '\n';
    std::cout << localizer.get("quit_option") << '\n';
    std::cout << "++++++++++++++++++++++++++++++\n";
    std::cout << "Option: ";
    
    std::string choice; 
    std::cin >> choice;
    
    if (choice == "1" || choice == "2" || choice == "3") {
        std::string billType;
        if (choice == "1") {
            billType = localizer.get("electricity").substr(4);
        } else if (choice == "2") {
            billType = localizer.get("water").substr(4);
        } else {
            billType = localizer.get("gas").substr(4);
        }
        
        char sub = showConfirmBackMain(localizer.get("pay_bills").substr(4) + " " + billType, m_menuManager);
        if (sub == 'C' || sub == 'c') {
            double amt;
            std::cout << localizer.get("bill_amount") << billType << localizer.get("bill_amount_suffix");
            if (!(std::cin >> amt)) {
                clearInput();
                std::cout << localizer.get("invalid_number");
                return MenuResult::Continue;
            }
            txService.payBill(amt, billType);
        } else if (sub == 'B' || sub == 'b' || sub == 'M' || sub == 'm') {
            m_menuManager.ChangeMenu(std::make_unique<TransactionMenu>(m_menuManager));
            return MenuResult::ClearAndContinue;
        }
        return MenuResult::Continue;
    } else if (choice == "B" || choice == "b") {
        m_menuManager.ChangeMenu(std::make_unique<TransactionMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (choice == "Q" || choice == "q") {
        return MenuResult::Exit;
    } else {
        std::cout << localizer.get("invalid_option") << '\n';
        return MenuResult::Continue;
    }
}

// TransactionDetailsMenu Implementation (remains the same)
TransactionDetailsMenu::TransactionDetailsMenu(MenuManager& menuManager, size_t index)
    : Menu(menuManager), transactionIndex(index) {}

MenuResult TransactionDetailsMenu::Display() {
    system("clear");
    
    auto& localizer = m_menuManager.getResources().getLocalizer();
    auto& txService = m_menuManager.getTransactionService();
    auto& user = m_menuManager.getUser();
    
    auto transaction = txService.getTransaction(transactionIndex);
    
    if (!transaction) {
        std::cout << localizer.get("invalid_transaction");
        std::cout << localizer.get("back_option") << '\n';
        std::cout << "Option: ";
        char ch; 
        std::cin >> ch;
        m_menuManager.ChangeMenu(std::make_unique<TransactionMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    }
    
    char time_str[26];
    ctime_r(&transaction->getTimestamp(), time_str);
    time_str[24] = '\0'; // Remove newline
    
    std::cout << "\n========================\n";
    std::cout << "Transaction Details for User: " << user.getUsername() << "\n";
    std::cout << "========================\n";
    std::cout << "Type: " << transactionTypeToString(transaction->getType()) << '\n';
    std::cout << "Amount: " << std::fixed << std::setprecision(2) 
              << transaction->getAmount() << " EGP\n";
    std::cout << "Description: " << transaction->getDescription() << '\n';
    std::cout << "Date: " << time_str << '\n';
    std::cout << "Status: " << transaction->getStatus() << '\n';
    std::cout << "========================\n";
    
    std::cout << localizer.get("back_option") << '\n';
    std::cout << localizer.get("main_menu") << '\n';
    std::cout << "Option: ";
    
    char ch; 
    std::cin >> ch;
    
    if (ch == 'B' || ch == 'b') {
        m_menuManager.ChangeMenu(std::make_unique<TransactionMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else if (ch == 'M' || ch == 'm') {
        m_menuManager.ChangeMenu(std::make_unique<OptionsMenu>(m_menuManager));
        return MenuResult::ClearAndContinue;
    } else {
        return MenuResult::Continue;
    }
}