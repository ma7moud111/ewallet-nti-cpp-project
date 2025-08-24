#pragma once
#include <string>

class User {
private:
    std::string username;
    std::string password;
public:
    User(const std::string& uname = "admin", const std::string& pass = "admin");
    bool login(const std::string& input_username, const std::string& input_pass) const;
    const std::string& getUsername() const;
    void setCredentials(const std::string& uname, const std::string& pass);
};
