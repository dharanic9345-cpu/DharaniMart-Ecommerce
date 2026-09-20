#include "UserRepository.h"
#include <sqlite3.h>
#include <drogon/drogon.h>

bool UserRepository::createUser(const User& user)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "INSERT INTO users (name, email, password_hash, role) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(statement, 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, user.email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, user.role.c_str(), -1, SQLITE_TRANSIENT);

    int result = sqlite3_step(statement);

    if (result != SQLITE_DONE)
    {
        LOG_ERROR << "User insert failed: "
                  << sqlite3_errmsg(db);
    }

    bool success = (result == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}

User UserRepository::findByEmail(const std::string& email)
{
    User user;

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return user;
    }

    const char* sql =
        "SELECT id, name, email, password_hash, role "
        "FROM users WHERE email = ?;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return user;
    }

    sqlite3_bind_text(
        statement,
        1,
        email.c_str(),
        -1,
        SQLITE_TRANSIENT);

    if (sqlite3_step(statement) == SQLITE_ROW)
    {
        user.id = sqlite3_column_int(statement, 0);

        user.name =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 1));

        user.email =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 2));

        user.passwordHash =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 3));

        user.role =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 4));
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return user;
}