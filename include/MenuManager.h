#pragma once
#include <memory>
#include <string>

class Menu;
class ApplicationResources;
class TransactionService;
class User;

class MenuManager {
private:
    std::unique_ptr<Menu> currentMenu;
    ApplicationResources& resources;
    std::unique_ptr<User> currentUser;
    std::unique_ptr<TransactionService> txService;

public:
    explicit MenuManager(ApplicationResources& res);
    ~MenuManager(); // Need explicit declaration for unique_ptr with incomplete types
    
    void ChangeMenu(std::unique_ptr<Menu> newMenu);
    void Run();
    void login(const std::string& username);
    void logout();
    
    User& getUser();
    TransactionService& getTransactionService();
    ApplicationResources& getResources() { return resources; }
    bool isLoggedIn() const;
};