#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "wallet.h"

class EWalletSystem {
private:
    User user;
    Wallet wallet;

public:
    EWalletSystem() : user("admin", "admin"), wallet() {}

    void run() {
        char option;
        bool loggedIn = false;

        while (true) {
            if (!loggedIn) {
                system("clear");
                std::cout << "\n\n=====================================================\n";
                std::cout << std::setw(40) << "Welcome to NTI smart wallet\n";
                std::cout << "=====================================================\n";
                std::cout << "Please select an action:\n\n";
                std::cout << "++++++++++++++++++++++\n";
                std::cout << "(L) Login\n";
                std::cout << "(Q) Quit\n";
                std::cout << "++++++++++++++++++++++\n";
                std::cout << "Option: ";
                std::cin >> option;

                if (option == 'L' || option == 'l') {
                    std::string uname, pass;
                    bool loginSuccess = false;

                    while (!loginSuccess) {
                        system("clear");
                        std::cout << "Please enter your username: ";
                        std::cin >> uname;
                        std::cout << "Please enter your password: ";
                        std::cin >> pass;

                        if (user.login(uname, pass)) {
                            loggedIn = true;
                            loginSuccess = true;
                            std::cout << "\nLogged in Successfully!\n";
                        } else {
                            char retryOption;
                            std::cout << "\nInvalid credentials!\n";
                            std::cout << "++++++++++++++++++++++\n";
                            std::cout << "(R) Retry\n";
                            std::cout << "(Q) Quit\n";
                            std::cout << "++++++++++++++++++++++\n";
                            std::cout << "Option: ";
                            std::cin >> retryOption;

                            if (retryOption == 'Q' || retryOption == 'q') {
                                std::cout << "Quitting...\n";
                                exit(0);
                            }
                            // If (R/r), loop continues and asks username & password again
                        }
                    }
                } 
                else if (option == 'Q' || option == 'q') {
                    std::cout << "Quitting...\n";
                    break;
                } 
                else {
                    std::cout << "Wrong option.. Try Again!\n";
                } 
            } else {
                // choose the number of service
                int serviceNo;
                std::cout << "\nPlease choose a service:\n";
                std::cout << "++++++++++++++++++++++++++++++\n";
                std::cout << "(1) Check Account Statement\n";
                std::cout << "(2) Check Balance\n";
                std::cout << "(3) Show Transaction History\n";
                std::cout << "(4) Withdraw\n";
                std::cout << "(5) Deposit\n";
                std::cout << "(6) Logout\n";
                std::cout << "++++++++++++++++++++++++++++++\n";
                std::cout << "Service No.: ";
                std::cin >> serviceNo;

                system("clear");
                switch (serviceNo) {
                    case 1:
                        std::cout << "Account Holder: " << user.getUsername() << "\n";
                        wallet.showBalance();
                        break;
                    case 2:
                        wallet.showBalance();
                        break;
                    case 3:
                        wallet.showTransactions();
                        break;
                    case 4: {
                        double amt;
                        std::cout << "Enter amount to withdraw: ";
                        std::cin >> amt;
                        wallet.withdraw(amt);
                        break;
                    }
                    case 5: {
                        double amt;
                        std::cout << "Enter amount to deposit: ";
                        std::cin >> amt;
                        wallet.deposit(amt);
                        break;
                    }
                    case 6:
                        loggedIn = false;
                        std::cout << "Logged out.\n";
                        break;
                    default:
                        std::cout << "Invalid option!\n";
                }
            }
        }
    }
};

int main() {
    EWalletSystem system;
    system.run();
    return 0;
}
