#pragma once

#include "../model/User.h"
#include "IUserRepository.h"

#include <string>
#include <vector>

class UserRepository : public IUserRepository
{
public:
    bool createUser(const User& user) override;

    User findByEmail(const std::string& email) override;
};