#include "OrderRepository.h"
#include <sqlite3.h>

bool OrderRepository::createOrder(
    int buyerId,
    double totalAmount)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "INSERT INTO orders "
        "(buyer_id, total_amount, status, payment_status) "
        "VALUES (?, ?, 'PLACED', 'PENDING');";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, buyerId);
    sqlite3_bind_double(statement, 2, totalAmount);

    bool success =
        (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}


std::vector<Order>
OrderRepository::getOrdersByBuyer(int buyerId)
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
        "WHERE buyer_id = ? "
        "ORDER BY id DESC;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return orders;
    }

    sqlite3_bind_int(statement, 1, buyerId);

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


bool OrderRepository::updatePaymentStatus(
    int orderId,
    const std::string& paymentStatus)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "UPDATE orders "
        "SET payment_status = ? "
        "WHERE id = ?;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(
        statement,
        1,
        paymentStatus.c_str(),
        -1,
        SQLITE_TRANSIENT);

    sqlite3_bind_int(statement, 2, orderId);

    bool success =
        (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}