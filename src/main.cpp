#include <drogon/drogon.h>
#include <sqlite3.h>
#include <fstream>
#include <sstream>
#include <string>

bool initializeDatabase()
{
    sqlite3* db = nullptr;

    if (sqlite3_open("db/dharani_mart.db", &db) != SQLITE_OK)
    {
        LOG_ERROR << "Database opening failed";
        return false;
    }

    std::ifstream file("db/migrations/V1__init_schema.sql");

    if (!file.is_open())
    {
        LOG_ERROR << "Schema file not found";
        sqlite3_close(db);
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sql = buffer.str();

    char* errorMessage = nullptr;

    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK)
    {
        LOG_ERROR << "Database schema creation failed: "
                  << errorMessage;

        sqlite3_free(errorMessage);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    LOG_INFO << "DharaniMart SQLite database initialized successfully";
    return true;
}

int main()
{
    bool dbReady = initializeDatabase();

    drogon::app()
        .setLogLevel(trantor::Logger::kInfo)
        .setDocumentRoot("./frontend")
        .addListener("127.0.0.1", 8080)
        .registerHandler(
            "/api/v1/health",
            [dbReady](
                const drogon::HttpRequestPtr&,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback)
            {
                Json::Value response;

                response["success"] = true;
                response["data"]["status"] = "UP";
                response["data"]["db"] =
                    dbReady ? "CONNECTED" : "NOT_CONNECTED";
                response["error"] = Json::nullValue;

                auto resp =
                    drogon::HttpResponse::newHttpJsonResponse(response);

                callback(resp);
            },
            {drogon::Get});

    LOG_INFO
        << "DharaniMart server starting on http://127.0.0.1:8080";

    drogon::app().run();

    return 0;
}