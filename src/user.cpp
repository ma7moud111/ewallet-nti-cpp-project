#include "user.h"

User::User(const std::string& uname, const std::string& pass)
    : username(uname), password(pass) {}

bool User::login(const std::string& input_username, const std::string& input_pass) const {
    return input_username == username && input_pass == password;
}

const std::string& User::getUsername() const { return username; }

void User::setCredentials(const std::string& uname, const std::string& pass) {
    username = uname; password = pass;
}
