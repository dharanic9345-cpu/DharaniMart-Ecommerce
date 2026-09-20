#pragma once

#include "../model/User.h"
#include "../repository/IUserRepository.h"

#include <string>

class UserService
{
private:
    IUserRepository& userRepository;

public:
    explicit UserService(IUserRepository& repository);

    bool registerUser(const User& user);

    User loginUser(
        const std::string& email,
        const std::string& password
    );
};