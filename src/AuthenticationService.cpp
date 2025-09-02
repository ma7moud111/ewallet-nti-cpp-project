#include "AuthenticationService.h"
#include "UserRepository.h"

AuthenticationService::AuthenticationService(UserRepository* r) : repo(r) {}

bool AuthenticationService::login(const std::string& uname, const std::string& pass) {
    return repo->authenticate(uname, pass);
}