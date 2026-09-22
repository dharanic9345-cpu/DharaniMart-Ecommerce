#pragma once

#include <libpq-fe.h>
#include <string>

class PostgreSQLConnection
{
private:
    PGconn* connection;

public:
    PostgreSQLConnection();

    ~PostgreSQLConnection();

    bool connect();

    void disconnect();

    PGconn* getConnection();
};