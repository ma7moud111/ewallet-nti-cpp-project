#include "menu_manager.h"
#include "menu.h"

int main() {
    MenuManager manager;
    manager.ChangeMenu(new WelcomeMenu(manager));
    manager.Run();
    return 0;
}
