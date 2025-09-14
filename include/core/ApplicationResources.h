#pragma once
#include "Settings.h"
#include <memory>

class Localizer;
class UserRepository;
class TransactionRepository;

class ApplicationResources {
private:
    Settings settings;
    std::unique_ptr<Localizer> localizer;
    std::unique_ptr<UserRepository> userRepo;
    std::unique_ptr<TransactionRepository> transactionRepo;

public:
    ApplicationResources();
    ~ApplicationResources(); // Need explicit declaration for unique_ptr with incomplete types

    Settings& getSettings() { return settings; }
    Localizer& getLocalizer() { return *localizer; }
    UserRepository& getUserRepository() { return *userRepo; }
    TransactionRepository& getTransactionRepository() { return *transactionRepo; }
};