#pragma once

#include "PostgreSQLConnection.h"
#include "../IUserRepository.h"
#include "../../model/User.h"

class PostgreSQLUserRepository : public IUserRepository
{
private:
    PostgreSQLConnection& database;

public:
    explicit PostgreSQLUserRepository(
        PostgreSQLConnection& connection
    );

    bool createUser(const User& user) override;

    User findByEmail(
        const std::string& email
    ) override;
};