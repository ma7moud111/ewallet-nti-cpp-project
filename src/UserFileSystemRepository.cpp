#include "UserFileSystemRepository.h"
#include "User.h"
#include <fstream>
#include <sstream>
#include <iostream>

UserFileSystemRepository::UserFileSystemRepository(const std::string& path) 
    : filePath(path) {
    initializeCSVFile();
}

void UserFileSystemRepository::initializeCSVFile() {
    std::ifstream testFile(filePath);
    if (!testFile) {
        // Create file with CSV header if it doesn't exist
        std::ofstream headerFile(filePath);
        if (headerFile) {
            headerFile << "username,password\n";
        }
    }
}

bool UserFileSystemRepository::authenticate(const std::string& username, const std::string& password) {
    std::ifstream file(filePath);
    if (!file) {
        return false;
    }
    
    std::string line;
    bool isFirstLine = true;
    
    while (std::getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false;
            continue; // Skip header
        }
        
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string storedUsername, storedPassword;
        
        if (std::getline(ss, storedUsername, ',') && std::getline(ss, storedPassword)) {
            // Trim whitespace
            storedUsername.erase(0, storedUsername.find_first_not_of(" \t\r\n"));
            storedUsername.erase(storedUsername.find_last_not_of(" \t\r\n") + 1);
            storedPassword.erase(0, storedPassword.find_first_not_of(" \t\r\n"));
            storedPassword.erase(storedPassword.find_last_not_of(" \t\r\n") + 1);
            
            if (storedUsername == username && storedPassword == password) {
                return true;
            }
        }
    }
    
    if (!file.eof() && file.fail()) {
        std::cerr << "Error reading from user file " << filePath << std::endl;
    }
    
    return false;
}

User* UserFileSystemRepository::findByUsername(const std::string& username) {
    std::ifstream file(filePath);
    if (!file) {
        return nullptr;
    }
    
    std::string line;
    bool isFirstLine = true;
    
    while (std::getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false;
            continue; // Skip header
        }
        
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string storedUsername, storedPassword;
        
        if (std::getline(ss, storedUsername, ',') && std::getline(ss, storedPassword)) {
            // Trim whitespace
            storedUsername.erase(0, storedUsername.find_first_not_of(" \t\r\n"));
            storedUsername.erase(storedUsername.find_last_not_of(" \t\r\n") + 1);
            storedPassword.erase(0, storedPassword.find_first_not_of(" \t\r\n"));
            storedPassword.erase(storedPassword.find_last_not_of(" \t\r\n") + 1);
            
            if (storedUsername == username) {
                return new User(storedUsername, storedPassword);
            }
        }
    }
    
    if (!file.eof() && file.fail()) {
        std::cerr << "Error reading from user file " << filePath << std::endl;
    }
    
    return nullptr;
}

void UserFileSystemRepository::save(const User& user) {
    std::ofstream file(filePath, std::ios::app);
    if (!file) {
        std::cerr << "Error: Could not open user file " << filePath << " for writing." << std::endl;
        return;
    }
    
    file << user.getUsername() << "," << user.getPassword() << "\n";
    if (!file) {
        std::cerr << "Error: Failed to write user to file." << std::endl;
    }
}