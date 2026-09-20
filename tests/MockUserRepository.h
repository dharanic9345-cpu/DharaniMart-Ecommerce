#pragma once
#include <gmock/gmock.h>
#include "../src/repository/IUserRepository.h"
class MockUserRepository : public IUserRepository
{
public:
    MOCK_METHOD(
        bool,
        createUser,
        (const User& user),
        (override)
    );
    MOCK_METHOD(
        User,
        findByEmail,
        (const std::string& email),
        (override)
    );
};
