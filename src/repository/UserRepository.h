#pragma once
#include "../model/User.h"
#include <string>
#include <vector>
class UserRepository
{
public:
    bool createUser(const User& user);
    User findByEmail(const std::string& email);
};
