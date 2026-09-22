#include "PostgreSQLConnection.h"
#include <iostream>

PostgreSQLConnection::PostgreSQLConnection()
    : connection(nullptr)
{
}

PostgreSQLConnection::~PostgreSQLConnection()
{
    disconnect();
}

bool PostgreSQLConnection::connect()
{
    connection = PQconnectdb(
        "host=localhost "
        "port=5432 "
        "dbname=dharani_mart "
        "user=postgres "
        "password=YOUR_NEW_PASSWORD"
    );

    if (PQstatus(connection) != CONNECTION_OK)
    {
        std::cout << "PostgreSQL connection failed!"
                  << std::endl;

        std::cout << PQerrorMessage(connection)
                  << std::endl;

        return false;
    }

    std::cout << "PostgreSQL connected successfully!"
              << std::endl;

    return true;
}

void PostgreSQLConnection::disconnect()
{
    if (connection != nullptr)
    {
        PQfinish(connection);
        connection = nullptr;
    }
}

PGconn* PostgreSQLConnection::getConnection()
{
    return connection;
}