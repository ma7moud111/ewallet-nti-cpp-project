#pragma once
#include <string>
#include "UserRepository.h"  // Replaced forward declaration with full include

class AuthenticationService {
private:
    UserRepository* repo;

public:
    AuthenticationService(UserRepository* r);
    bool login(const std::string& uname, const std::string& pass);
    UserRepository* getRepo() { return repo; }  // Added for registration
};