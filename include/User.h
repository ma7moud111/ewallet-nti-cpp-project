#pragma once
#include <string>

class User {
private:
    std::string username;
    std::string password;
public:
    User(const std::string& uname, const std::string& pass) : username(uname), password(pass) {}
    const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }
};