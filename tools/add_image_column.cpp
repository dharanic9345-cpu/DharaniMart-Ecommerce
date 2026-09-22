#include <sqlite3.h>
#include <iostream>

int main()
{
    sqlite3* db = nullptr;

    int result = sqlite3_open(
        "db/dharani_mart.db",
        &db
    );

    if (result != SQLITE_OK)
    {
        std::cout << "Database open failed: "
                  << sqlite3_errmsg(db)
                  << std::endl;

        sqlite3_close(db);
        return 1;
    }

    const char* sql =
        "ALTER TABLE products "
        "ADD COLUMN image_url TEXT DEFAULT '';";

    char* errorMessage = nullptr;

    result = sqlite3_exec(
        db,
        sql,
        nullptr,
        nullptr,
        &errorMessage
    );

    if (result != SQLITE_OK)
    {
        std::cout << "Column add failed: "
                  << errorMessage
                  << std::endl;

        sqlite3_free(errorMessage);
        sqlite3_close(db);
        return 1;
    }

    std::cout << "image_url column added successfully!"
              << std::endl;

    sqlite3_close(db);

    return 0;
}