#include "Application.h"
#include "ApplicationResources.h"
#include "MenuManager.h"

Application::Application() 
    : resources(std::make_unique<ApplicationResources>())
    , menuManager(std::make_unique<MenuManager>(*resources)) {
}

Application::~Application() = default;

void Application::start() {
    menuManager->Run();
}