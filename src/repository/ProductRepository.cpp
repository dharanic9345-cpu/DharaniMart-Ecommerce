#include "ProductRepository.h"
#include <sqlite3.h>

bool ProductRepository::createProduct(const Product& product)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "INSERT INTO products "
        "(seller_id, name, description, price, stock, category) "
        "VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, product.sellerId);
    sqlite3_bind_text(statement, 2, product.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, product.description.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 4, product.price);
    sqlite3_bind_int(statement, 5, product.stock);
    sqlite3_bind_text(statement, 6, product.category.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}


std::vector<Product>
ProductRepository::getProductsBySeller(int sellerId)
{
    std::vector<Product> products;

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return products;
    }

    const char* sql =
        "SELECT id, seller_id, name, description, price, stock, category "
        "FROM products WHERE seller_id = ?;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return products;
    }

    sqlite3_bind_int(statement, 1, sellerId);

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        Product product;

        product.id = sqlite3_column_int(statement, 0);
        product.sellerId = sqlite3_column_int(statement, 1);

        product.name =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));

        product.description =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));

        product.price = sqlite3_column_double(statement, 4);
        product.stock = sqlite3_column_int(statement, 5);

        product.category =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 6));

        products.push_back(product);
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return products;
}


std::vector<Product>
ProductRepository::getAllProducts()
{
    std::vector<Product> products;

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return products;
    }

    const char* sql =
        "SELECT id, seller_id, name, description, price, stock, category "
        "FROM products;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return products;
    }

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        Product product;

        product.id = sqlite3_column_int(statement, 0);
        product.sellerId = sqlite3_column_int(statement, 1);

        product.name =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));

        product.description =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));

        product.price = sqlite3_column_double(statement, 4);
        product.stock = sqlite3_column_int(statement, 5);

        product.category =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 6));

        products.push_back(product);
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return products;
}


// SEARCH + CATEGORY FILTER
std::vector<Product>
ProductRepository::searchProducts(
    const std::string& keyword,
    const std::string& category)
{
    std::vector<Product> products;

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return products;
    }

    const char* sql =
        "SELECT id, seller_id, name, description, price, stock, category "
        "FROM products "
        "WHERE (name LIKE ? OR description LIKE ?) "
        "AND (? = '' OR category = ?);";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return products;
    }

    std::string searchPattern = "%" + keyword + "%";

    sqlite3_bind_text(
        statement,
        1,
        searchPattern.c_str(),
        -1,
        SQLITE_TRANSIENT);

    sqlite3_bind_text(
        statement,
        2,
        searchPattern.c_str(),
        -1,
        SQLITE_TRANSIENT);

    sqlite3_bind_text(
        statement,
        3,
        category.c_str(),
        -1,
        SQLITE_TRANSIENT);

    sqlite3_bind_text(
        statement,
        4,
        category.c_str(),
        -1,
        SQLITE_TRANSIENT);

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        Product product;

        product.id = sqlite3_column_int(statement, 0);
        product.sellerId = sqlite3_column_int(statement, 1);

        product.name =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));

        product.description =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));

        product.price = sqlite3_column_double(statement, 4);
        product.stock = sqlite3_column_int(statement, 5);

        product.category =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 6));

        products.push_back(product);
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return products;
}


bool ProductRepository::updateProduct(
    const Product& product)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "UPDATE products "
        "SET name = ?, description = ?, price = ?, "
        "stock = ?, category = ? "
        "WHERE id = ? AND seller_id = ?;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(statement, 1, product.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, product.description.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 3, product.price);
    sqlite3_bind_int(statement, 4, product.stock);
    sqlite3_bind_text(statement, 5, product.category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 6, product.id);
    sqlite3_bind_int(statement, 7, product.sellerId);

    bool success = (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}


bool ProductRepository::deleteProduct(
    int productId,
    int sellerId)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "DELETE FROM products "
        "WHERE id = ? AND seller_id = ?;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, productId);
    sqlite3_bind_int(statement, 2, sellerId);

    bool success = (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}