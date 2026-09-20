#pragma once
#include "../model/User.h"
#include "../repository/UserRepository.h"
class UserService
{
private:
    UserRepository userRepository;
public:
    bool registerUser(const User& user);
    User loginUser(const std::string& email, const std::string& password);
};
