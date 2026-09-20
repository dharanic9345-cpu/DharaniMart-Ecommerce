#pragma once

#include "../model/User.h"
#include <string>

class IUserRepository
{
public:
    virtual ~IUserRepository() = default;

    virtual bool createUser(const User& user) = 0;

    virtual User findByEmail(const std::string& email) = 0;
};