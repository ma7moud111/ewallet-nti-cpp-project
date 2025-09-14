#include "UserInMemoryRepository.h"
#include "User.h"

UserInMemoryRepository::UserInMemoryRepository() {
    users["admin"] = "admin";
    // Add more users if needed
}

bool UserInMemoryRepository::authenticate(const std::string& uname, const std::string& pass) {
    auto it = users.find(uname);
    if (it != users.end() && it->second == pass) return true;
    return false;
}

User* UserInMemoryRepository::findByUsername(const std::string& uname) {
    auto it = users.find(uname);
    if (it != users.end()) {
        return new User(uname, it->second);
    }
    return nullptr;
}

void UserInMemoryRepository::save(const User& user) {
    users[user.getUsername()] = user.getPassword();
}