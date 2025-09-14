#ifndef USER_FILE_SYSTEM_REPOSITORY_H
#define USER_FILE_SYSTEM_REPOSITORY_H
#include "UserRepository.h"
#include <string>

class UserFileSystemRepository : public UserRepository {
private:
    std::string filePath;
    void initializeCSVFile();

public:
    explicit UserFileSystemRepository(const std::string& path);
    bool authenticate(const std::string& username, const std::string& password) override;
    User* findByUsername(const std::string& username) override;
    void save(const User& user) override;
};

#endif