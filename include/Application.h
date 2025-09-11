#pragma once
#include <memory>

class ApplicationResources;
class MenuManager;

class Application {
private:
    std::unique_ptr<ApplicationResources> resources;
    std::unique_ptr<MenuManager> menuManager;

public:
    Application();
    ~Application(); 
    void start();
};