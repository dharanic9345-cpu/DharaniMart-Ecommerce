#include "UserController.h"
UserController::UserController()
    : userRepository(),
      userService(userRepository)
{
}
void UserController::registerUser(
    const drogon::HttpRequestPtr& request,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    LOG_INFO << "Request body: " << request->getBody();

    Json::Value response;

    auto json = request->getJsonObject();

    if (!json)
    {
        response["success"] = false;
        response["message"] = "Invalid JSON";

        auto resp =
            drogon::HttpResponse::newHttpJsonResponse(response);

        callback(resp);
        return;
    }

    User user;

    user.name = (*json)["name"].asString();
    user.email = (*json)["email"].asString();
    user.passwordHash = (*json)["password"].asString();
    user.role = (*json)["role"].asString();

    if (user.role.empty())
    {
        user.role = "BUYER";
    }

    bool success = userService.registerUser(user);

    response["success"] = success;

    if (success)
    {
        response["message"] = "Registration successful";
    }
    else
    {
        response["message"] = "Registration failed";
    }

    auto resp =
        drogon::HttpResponse::newHttpJsonResponse(response);

    callback(resp);
}

void UserController::loginUser(
    const drogon::HttpRequestPtr& request,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    auto json = request->getJsonObject();

    if (!json)
    {
        response["success"] = false;
        response["message"] = "Invalid JSON";

        auto resp =
            drogon::HttpResponse::newHttpJsonResponse(response);

        callback(resp);
        return;
    }

    std::string email = (*json)["email"].asString();
    std::string password = (*json)["password"].asString();

    User user = userService.loginUser(email, password);

    if (user.id != 0)
    {
        response["success"] = true;
        response["message"] = "Login successful";
        response["data"]["name"] = user.name;
        response["data"]["email"] = user.email;
        response["data"]["role"] = user.role;
    }
    else
    {
        response["success"] = false;
        response["message"] = "Invalid email or password";
    }

    auto resp =
        drogon::HttpResponse::newHttpJsonResponse(response);

    callback(resp);
}