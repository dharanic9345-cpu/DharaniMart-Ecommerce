#include "CartRepository.h"
#include <sqlite3.h>

bool CartRepository::addToCart(
    int buyerId,
    int productId,
    int quantity)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    // Create cart if buyer does not have one
    const char* cartSql =
        "INSERT OR IGNORE INTO cart (buyer_id) VALUES (?);";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, cartSql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, buyerId);

    if (sqlite3_step(statement) != SQLITE_DONE)
    {
        sqlite3_finalize(statement);
        sqlite3_close(db);
        return false;
    }

    sqlite3_finalize(statement);

    // Get cart ID
    const char* findCartSql =
        "SELECT id FROM cart WHERE buyer_id = ?;";

    if (sqlite3_prepare_v2(
            db, findCartSql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, buyerId);

    int cartId = 0;

    if (sqlite3_step(statement) == SQLITE_ROW)
    {
        cartId = sqlite3_column_int(statement, 0);
    }

    sqlite3_finalize(statement);

    if (cartId == 0)
    {
        sqlite3_close(db);
        return false;
    }

    // Add product or increase existing quantity
    const char* itemSql =
        "INSERT INTO cart_items "
        "(cart_id, product_id, quantity) "
        "VALUES (?, ?, ?) "
        "ON CONFLICT(cart_id, product_id) "
        "DO UPDATE SET quantity = quantity + excluded.quantity;";

    if (sqlite3_prepare_v2(
            db, itemSql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, cartId);
    sqlite3_bind_int(statement, 2, productId);
    sqlite3_bind_int(statement, 3, quantity);

    bool success =
        (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}


std::vector<CartItem>
CartRepository::getCartItems(int buyerId)
{
    std::vector<CartItem> items;

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return items;
    }

    const char* sql =
        "SELECT ci.id, ci.cart_id, ci.product_id, ci.quantity "
        "FROM cart_items ci "
        "JOIN cart c ON ci.cart_id = c.id "
        "WHERE c.buyer_id = ?;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return items;
    }

    sqlite3_bind_int(statement, 1, buyerId);

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        CartItem item;

        item.id =
            sqlite3_column_int(statement, 0);

        item.cartId =
            sqlite3_column_int(statement, 1);

        item.productId =
            sqlite3_column_int(statement, 2);

        item.quantity =
            sqlite3_column_int(statement, 3);

        items.push_back(item);
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return items;
}


bool CartRepository::updateCartItem(
    int buyerId,
    int productId,
    int quantity)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "UPDATE cart_items "
        "SET quantity = ? "
        "WHERE product_id = ? "
        "AND cart_id = "
        "(SELECT id FROM cart WHERE buyer_id = ?);";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, quantity);
    sqlite3_bind_int(statement, 2, productId);
    sqlite3_bind_int(statement, 3, buyerId);

    bool success =
        (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}


bool CartRepository::removeFromCart(
    int buyerId,
    int productId)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "DELETE FROM cart_items "
        "WHERE product_id = ? "
        "AND cart_id = "
        "(SELECT id FROM cart WHERE buyer_id = ?);";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, productId);
    sqlite3_bind_int(statement, 2, buyerId);

    bool success =
        (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}


bool CartRepository::clearCart(int buyerId)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "DELETE FROM cart_items "
        "WHERE cart_id = "
        "(SELECT id FROM cart WHERE buyer_id = ?);";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, buyerId);

    bool success =
        (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}