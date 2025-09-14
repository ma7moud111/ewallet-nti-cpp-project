#!/bin/bash
# Create new directory structure
mkdir -p src/{core,services,repositories,models,ui,config}
mkdir -p include/{core,services,repositories,models,ui,config}
mkdir -p build/{core,services,repositories,models,ui,config}
mkdir -p data docs

# Create placeholder for data directory
touch data/.gitkeep


mv include/Application.h include/core/
mv include/ApplicationResources.h include/core/


mv include/TransactionService.h include/services/
mv include/AuthenticationService.h include/services/



mv include/UserRepository.h include/repositories/
mv include/UserInMemoryRepository.h include/repositories/
mv include/UserFileSystemRepository.h include/repositories/
mv include/TransactionRepository.h include/repositories/
mv include/TransactionInMemoryRepository.h include/repositories/
mv include/TransactionFileSystemRepository.h include/repositories/


mv include/User.h include/models/
mv include/TransactionDetails.h include/models/
mv include/TransactionType.h include/models/


mv include/Menu.h include/ui/
mv include/MenuManager.h include/ui/
mv include/Localizer.h include/ui/

mv include/Settings.h include/config/

mv src/Application.cpp src/core/
mv src/ApplicationResources.cpp src/core/
mv src/main.cpp src/core/

mv src/TransactionService.cpp src/services/
mv src/AuthenticationService.cpp src/services/

mv src/UserInMemoryRepository.cpp src/repositories/
mv src/UserFileSystemRepository.cpp src/repositories/
mv src/TransactionInMemoryRepository.cpp src/repositories/
mv src/TransactionFileSystemRepository.cpp src/repositories/

mv src/TransactionDetails.cpp src/models/
mv src/TransactionType.cpp src/models/
# Note: User.h is header-only, no .cpp file to move

mv src/Menu.cpp src/ui/
mv src/MenuManager.cpp src/ui/
mv src/Localizer.cpp src/ui/

# Settings is currently header-only, but if you create Settings.cpp:
# mv src/Settings.cpp src/config/