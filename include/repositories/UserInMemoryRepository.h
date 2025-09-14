#pragma once
#include "UserRepository.h"
#include <string>
#include <unordered_map>

class UserInMemoryRepository : public UserRepository {
public:
    UserInMemoryRepository();
    bool authenticate(const std::string& uname, const std::string& pass) override;
    User* findByUsername(const std::string& uname) override;
    void save(const User& user) override;

private:
    std::unordered_map<std::string, std::string> users;
};