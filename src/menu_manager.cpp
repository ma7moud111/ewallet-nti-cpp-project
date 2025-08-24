#include "menu_manager.h"
#include "menu.h"
#include <cstdlib>

MenuManager::MenuManager() : m_currentMenu(nullptr), m_user("admin","admin"), m_wallet() {}

MenuManager::MenuManager(Menu* firstMenu) : m_currentMenu(firstMenu), m_user("admin","admin"), m_wallet() {}

MenuManager::~MenuManager() {
    delete m_currentMenu;
}

void MenuManager::ChangeMenu(Menu* newMenu) {
    delete m_currentMenu;
    m_currentMenu = newMenu;
}

void MenuManager::Run() {
    if (!m_currentMenu) {
        ChangeMenu(new WelcomeMenu(*this));
    }

    bool running = true;
    while (running) {
        MenuResult res = m_currentMenu->Display();
        switch (res) {
            case MenuResult::Continue:
                break;
            case MenuResult::ClearAndContinue:
                system("clear");
                break;
            case MenuResult::Exit:
                running = false; 
                break;
        }
        if (res == MenuResult::Exit) running = false;
    }
}
