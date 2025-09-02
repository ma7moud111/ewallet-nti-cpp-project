#pragma once

#include <string>

class User;

class UserRepository {
public:
    virtual ~UserRepository() = default;
    virtual bool authenticate(const std::string& uname, const std::string& pass) = 0;
    virtual User* findByUsername(const std::string& uname) = 0;
    virtual void save(const User& user) = 0;
};