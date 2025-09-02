#pragma once

class Settings;
class Localizer;
class UserRepository;
class AuthenticationService;
class MenuManager;

class Application {
private:
    Settings* settings;
    Localizer* localizer;
    UserRepository* userRepo;
    AuthenticationService* authService;
    MenuManager* menuManager;

public:
    Application();
    ~Application();
    void start();
};