#include "Application.h"
#include "Settings.h"
#include "Localizer.h"
#include "UserRepository.h"
#include "UserInMemoryRepository.h"
#include "UserFileSystemRepository.h"
#include "AuthenticationService.h"
#include "MenuManager.h"

Application::Application() {
    settings = new Settings();
    localizer = new Localizer(*settings);

    if (settings->userRepoType == "InMemory") {
        userRepo = new UserInMemoryRepository();
    } else {
        userRepo = new UserFileSystemRepository("users.txt");
    }

    authService = new AuthenticationService(userRepo);
    menuManager = new MenuManager(*authService, *settings);
}

Application::~Application() {
    delete menuManager;
    delete authService;
    delete userRepo;
    delete localizer;
    delete settings;
}

void Application::start() {
    menuManager->Run();
}