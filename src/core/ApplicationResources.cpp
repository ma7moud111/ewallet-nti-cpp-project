#include "ApplicationResources.h"
#include "Localizer.h"
#include "UserRepository.h"
#include "UserInMemoryRepository.h"
#include "UserFileSystemRepository.h"
#include "TransactionRepository.h"
#include "TransactionInMemoryRepository.h"
#include "TransactionFileSystemRepository.h"

ApplicationResources::ApplicationResources() {
    localizer = std::make_unique<Localizer>(settings);
    
    if (settings.userRepoType == "InMemory") {
        userRepo = std::make_unique<UserInMemoryRepository>();
    } else {
        userRepo = std::make_unique<UserFileSystemRepository>("users.csv");
    }
    
    if (settings.txRepoType == "InMemory") {
        transactionRepo = std::make_unique<TransactionInMemoryRepository>();
    } else {
        transactionRepo = std::make_unique<TransactionFileSystemRepository>("transactions.csv");
    }
}

ApplicationResources::~ApplicationResources() = default;