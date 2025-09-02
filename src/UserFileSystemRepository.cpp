#include "UserFileSystemRepository.h"
#include "User.h"
#include <fstream>
#include <sstream>

UserFileSystemRepository::UserFileSystemRepository(const std::string& path) : filePath(path) {}

bool UserFileSystemRepository::authenticate(const std::string& username, const std::string& password) {
    std::ifstream file(filePath);
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername, storedPassword;
        if (std::getline(ss, storedUsername, ',') && std::getline(ss, storedPassword, ',')) {
            if (storedUsername == username && storedPassword == password) {
                return true;
            }
        }
    }
    return false;
}

User* UserFileSystemRepository::findByUsername(const std::string& username) {
    std::ifstream file(filePath);
    if (!file) return nullptr;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername, storedPassword;
        if (std::getline(ss, storedUsername, ',') && std::getline(ss, storedPassword, ',')) {
            if (storedUsername == username) {
                return new User(storedUsername, storedPassword);
            }
        }
    }
    return nullptr;
}

void UserFileSystemRepository::save(const User& user) {
    std::ofstream file(filePath, std::ios::app);
    if (file) {
        file << user.getUsername() << "," << user.getPassword() << "\n";
    }
}