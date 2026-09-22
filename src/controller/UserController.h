#pragma once

#include "../service/UserService.h"
#include "../repository/PostgreSQL/PostgreSQLUserRepository.h"
#include "../repository/PostgreSQL/PostgreSQLConnection.h"

#include <drogon/HttpController.h>

class UserController
    : public drogon::HttpController<UserController>
{
public:

    UserController();

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        UserController::registerUser,
        "/api/v1/auth/register",
        drogon::Post
    );

    ADD_METHOD_TO(
        UserController::loginUser,
        "/api/v1/auth/login",
        drogon::Post
    );

    METHOD_LIST_END

    void registerUser(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback
    );

    void loginUser(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback
    );

private:

    PostgreSQLConnection database;

    PostgreSQLUserRepository userRepository;

    UserService userService;
};