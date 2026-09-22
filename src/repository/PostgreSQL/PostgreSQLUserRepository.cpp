#include "PostgreSQLUserRepository.h"

#include <libpq-fe.h>
#include <iostream>

PostgreSQLUserRepository::PostgreSQLUserRepository(
    PostgreSQLConnection& connection)
    : database(connection)
{
}

bool PostgreSQLUserRepository::createUser(
    const User& user)
{
    PGconn* connection = database.getConnection();

    if (connection == nullptr)
    {
        return false;
    }

    const char* query =
        "INSERT INTO users "
        "(name, email, password_hash, role) "
        "VALUES ($1, $2, $3, $4);";

    const char* values[4];

    values[0] = user.name.c_str();
    values[1] = user.email.c_str();
    values[2] = user.passwordHash.c_str();
    values[3] = user.role.c_str();

    PGresult* result = PQexecParams(
        connection,
        query,
        4,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        std::cout
            << "User creation failed: "
            << PQerrorMessage(connection)
            << std::endl;

        PQclear(result);
        return false;
    }

    PQclear(result);

    return true;
}

User PostgreSQLUserRepository::findByEmail(
    const std::string& email)
{
    User user;

    PGconn* connection = database.getConnection();

    if (connection == nullptr)
    {
        return user;
    }

    const char* query =
        "SELECT id, name, email, password_hash, role "
        "FROM users "
        "WHERE email = $1;";

    const char* values[1];

    values[0] = email.c_str();

    PGresult* result = PQexecParams(
        connection,
        query,
        1,
        nullptr,
        values,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        PQclear(result);
        return user;
    }

    if (PQntuples(result) == 1)
    {
        user.id =
            std::stoi(PQgetvalue(result, 0, 0));

        user.name =
            PQgetvalue(result, 0, 1);

        user.email =
            PQgetvalue(result, 0, 2);

        user.passwordHash =
            PQgetvalue(result, 0, 3);

        user.role =
            PQgetvalue(result, 0, 4);
    }

    PQclear(result);

    return user;
}