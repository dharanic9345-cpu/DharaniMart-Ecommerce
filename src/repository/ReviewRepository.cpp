#include "ReviewRepository.h"
#include <sqlite3.h>

bool ReviewRepository::addReview(const Review& review)
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return false;
    }

    const char* sql =
        "INSERT INTO reviews "
        "(product_id, buyer_id, rating, comment) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(statement, 1, review.productId);
    sqlite3_bind_int(statement, 2, review.buyerId);
    sqlite3_bind_int(statement, 3, review.rating);

    sqlite3_bind_text(
        statement,
        4,
        review.comment.c_str(),
        -1,
        SQLITE_TRANSIENT);

    bool success =
        (sqlite3_step(statement) == SQLITE_DONE);

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return success;
}


std::vector<Review>
ReviewRepository::getReviewsByProduct(int productId)
{
    std::vector<Review> reviews;

    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        return reviews;
    }

    const char* sql =
        "SELECT id, product_id, buyer_id, rating, comment "
        "FROM reviews "
        "WHERE product_id = ? "
        "ORDER BY id DESC;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        return reviews;
    }

    sqlite3_bind_int(statement, 1, productId);

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        Review review;

        review.id =
            sqlite3_column_int(statement, 0);

        review.productId =
            sqlite3_column_int(statement, 1);

        review.buyerId =
            sqlite3_column_int(statement, 2);

        review.rating =
            sqlite3_column_int(statement, 3);

        const unsigned char* comment =
            sqlite3_column_text(statement, 4);

        if (comment != nullptr)
        {
            review.comment =
                reinterpret_cast<const char*>(comment);
        }

        reviews.push_back(review);
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return reviews;
}