#include <iostream>

#include "../src/repository/PostgreSQL/PostgreSQLConnection.h"
#include "../src/repository/PostgreSQL/PostgreSQLUserRepository.h"

int main()
{
    PostgreSQLConnection database;

    if (!database.connect())
    {
        std::cout << "Database connection failed!" << std::endl;
        return 1;
    }

    PostgreSQLUserRepository repository(database);

    User user;

    user.name = "PostgreSQL Test User";
    user.email = "postgres_test@gmail.com";
    user.passwordHash = "test_hash";
    user.role = "BUYER";

    bool created = repository.createUser(user);

    if (created)
    {
        std::cout << "User created successfully!" << std::endl;
    }
    else
    {
        std::cout << "User creation failed!" << std::endl;
    }

    User found =
        repository.findByEmail("postgres_test@gmail.com");

    if (found.id != 0)
    {
        std::cout << "User found successfully!" << std::endl;
        std::cout << "Name: " << found.name << std::endl;
        std::cout << "Email: " << found.email << std::endl;
        std::cout << "Role: " << found.role << std::endl;
    }
    else
    {
        std::cout << "User not found!" << std::endl;
    }

    return 0;
}