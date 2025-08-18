#include <cstdlib>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <iomanip>
#include "wallet.h"


std::string username = "admin";
std::string pass = "admin";



int main()
{
    std::string input_username;
    std::string input_pass;
    char option;
    int serviceNo;
    SmartWallet sw;

    system("clear");
    std::cout<<std::endl<<std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout <<std::setw(40)<< "Welcome to NTI smart wallet" << std::endl;
    std::cout << "=====================================================" << std::endl;
    while(true)
    {
        std::cout << "Please select an action: " << std::endl<<std::endl ;
        std::cout << "++++++++++++++++++++++" << std::endl;
        std::cout << "(L) Login" << std::endl;
        std::cout << "(Q) Quit" << std::endl;
        std::cout << "++++++++++++++++++++++" << std::endl;
        std::cout << "Option: ";
        std::cin >> option;

        bool flag = false;

        if(option == 'L') 
        {
            system("clear");
            std::cout << "please enter your username: ";
            std::cin >> input_username;
            std::cout << "please enter your password: ";
            std::cin >> input_pass;
            if(input_username == username && input_pass == pass)
            {
                sw.setUserData(input_username, input_pass);
                flag = true;
            }
            else{
                system("clear");
                std::cout << "Try Again!" << std::endl;
                flag = false;
                continue;
            }

        
        }else if(option == 'Q'){
            system("clear");
            std::cout << "quitting..." << std::endl;
            break;
        }
        else{
            system("clear");
            std::cout << "Wrong option..Try Again!" << std::endl;
            continue;
        }

        if(flag)
        {
            system("clear");
            std::cout << "Logged in Successfully!" <<std::endl<<std::endl;
            std::cout << "Please choose the service: " <<std::endl;
            std::cout << "++++++++++++++++++++++++++++++" << std::endl;
            std::cout << "(1) Check Account Statment" <<std::endl;
            std::cout << "(2) Check balance" <<std::endl;
            std::cout << "(3) Show Transaction History" <<std::endl;
            std::cout << "(4) Withdraw" <<std::endl;
            std::cout << "(5) Deposite" <<std::endl;
            std::cout << "++++++++++++++++++++++++++++++" << std::endl;
            std::cout << "Service No.: ";
            std::cin >> serviceNo;

        }

    }


    return 0;
}