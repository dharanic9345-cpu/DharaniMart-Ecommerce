#include <iostream>
#include <libpq-fe.h>

int main()
{
    std::cout << "PostgreSQL test started!" << std::endl;

    PGconn* connection = PQconnectdb(
        "host=localhost "
        "port=5432 "
        "dbname=dharani_mart "
        "user=postgres "
        "password=YOUR_NEW_PASSWORD"
    );

    if (PQstatus(connection) != CONNECTION_OK)
    {
        std::cout << "PostgreSQL connection failed!" << std::endl;
        std::cout << PQerrorMessage(connection) << std::endl;

        PQfinish(connection);
        return 1;
    }

    std::cout << "PostgreSQL connected successfully!" << std::endl;

    PQfinish(connection);

    return 0;
}