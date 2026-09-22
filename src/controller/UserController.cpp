#include "UserController.h"

UserController::UserController()
    : database(),
      userRepository(database),
      userService(userRepository)
{
    database.connect();
}

void UserController::registerUser(
    const drogon::HttpRequestPtr& request,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    response["success"] = false;

    if (!request->getJsonObject())
    {
        response["message"] = "Invalid JSON";

        callback(
            drogon::HttpResponse::newHttpJsonResponse(response)
        );

        return;
    }

    auto json = request->getJsonObject();

    User user;

    user.name =
        (*json)["name"].asString();

    user.email =
        (*json)["email"].asString();

    user.passwordHash =
        (*json)["password"].asString();

    user.role =
        (*json)["role"].asString();

    if (user.role.empty())
    {
        user.role = "BUYER";
    }

    bool result =
        userService.registerUser(user);

    response["success"] = result;

    response["message"] =
        result
            ? "Registration successful"
            : "Registration failed";

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response)
    );
}

void UserController::loginUser(
    const drogon::HttpRequestPtr& request,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    response["success"] = false;

    if (!request->getJsonObject())
    {
        response["message"] = "Invalid JSON";

        callback(
            drogon::HttpResponse::newHttpJsonResponse(response)
        );

        return;
    }

    auto json = request->getJsonObject();

    std::string email =
        (*json)["email"].asString();

    std::string password =
        (*json)["password"].asString();

    User user =
        userService.loginUser(
            email,
            password
        );

    if (user.id != 0)
    {
        response["success"] = true;
        response["message"] = "Login successful";

        response["user"]["id"] = user.id;
        response["user"]["name"] = user.name;
        response["user"]["email"] = user.email;
        response["user"]["role"] = user.role;
    }
    else
    {
        response["message"] =
            "Invalid email or password";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response)
    );
}