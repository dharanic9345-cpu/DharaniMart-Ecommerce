#include "AdminRepository.h"
#include <sqlite3.h>

std::vector<User> AdminRepository::getAllUsers()
{
    std::vector<User> users;

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return users;
    }

    const char* sql =
        "SELECT id, name, email, password_hash, role "
        "FROM users "
        "ORDER BY id;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return users;
    }

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        User user;

        user.id =
            sqlite3_column_int(statement, 0);

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

        users.push_back(user);
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return users;
}


std::vector<Product> AdminRepository::getAllProducts()
{
    std::vector<Product> products;

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return products;
    }

    const char* sql =
        "SELECT id, seller_id, name, description, "
        "price, stock, category "
        "FROM products "
        "ORDER BY id;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return products;
    }

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        Product product;

        product.id =
            sqlite3_column_int(statement, 0);

        product.sellerId =
            sqlite3_column_int(statement, 1);

        product.name =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 2));

        const unsigned char* description =
            sqlite3_column_text(statement, 3);

        if (description != nullptr)
        {
            product.description =
                reinterpret_cast<const char*>(description);
        }

        product.price =
            sqlite3_column_double(statement, 4);

        product.stock =
            sqlite3_column_int(statement, 5);

        const unsigned char* category =
            sqlite3_column_text(statement, 6);

        if (category != nullptr)
        {
            product.category =
                reinterpret_cast<const char*>(category);
        }

        products.push_back(product);
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return products;
}


std::vector<Order> AdminRepository::getAllOrders()
{
    std::vector<Order> orders;

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return orders;
    }

    const char* sql =
        "SELECT id, buyer_id, total_amount, "
        "status, payment_status "
        "FROM orders "
        "ORDER BY id DESC;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return orders;
    }

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        Order order;

        order.id =
            sqlite3_column_int(statement, 0);

        order.buyerId =
            sqlite3_column_int(statement, 1);

        order.totalAmount =
            sqlite3_column_double(statement, 2);

        order.status =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 3));

        order.paymentStatus =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 4));

        orders.push_back(order);
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return orders;
}


bool AdminRepository::deleteUser(int userId)
{
    if (userId <= 0)
    {
        return false;
    }

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "DELETE FROM users "
        "WHERE id = ?;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, userId);

    bool success = false;

    if (sqlite3_step(statement) == SQLITE_DONE)
    {
        if (sqlite3_changes(db) > 0)
        {
            success = true;
        }
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}
bool AdminRepository::deleteProduct(int productId)
{
    if (productId <= 0)
    {
        return false;
    }

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "DELETE FROM products "
        "WHERE id = ?;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, productId);

    bool success = false;

    if (sqlite3_step(statement) == SQLITE_DONE)
    {
        if (sqlite3_changes(db) > 0)
        {
            success = true;
        }
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}