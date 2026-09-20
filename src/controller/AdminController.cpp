#include "AdminController.h"


void AdminController::getAllUsers(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    auto users = adminService.getAllUsers();

    response["success"] = true;
    response["data"] = Json::arrayValue;

    for (const auto& user : users)
    {
        Json::Value data;

        data["id"] = user.id;
        data["name"] = user.name;
        data["email"] = user.email;
        data["role"] = user.role;

        // Password hash is not returned.

        response["data"].append(data);
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void AdminController::getAllProducts(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    auto products =
        adminService.getAllProducts();

    response["success"] = true;
    response["data"] = Json::arrayValue;

    for (const auto& product : products)
    {
        Json::Value data;

        data["id"] = product.id;
        data["sellerId"] = product.sellerId;
        data["name"] = product.name;
        data["description"] = product.description;
        data["price"] = product.price;
        data["stock"] = product.stock;
        data["category"] = product.category;

        response["data"].append(data);
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void AdminController::getAllOrders(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    auto orders =
        adminService.getAllOrders();

    response["success"] = true;
    response["data"] = Json::arrayValue;

    for (const auto& order : orders)
    {
        Json::Value data;

        data["id"] = order.id;
        data["buyerId"] = order.buyerId;
        data["totalAmount"] = order.totalAmount;
        data["status"] = order.status;
        data["paymentStatus"] = order.paymentStatus;

        response["data"].append(data);
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void AdminController::deleteUser(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    int userId)
{
    Json::Value response;

    bool success =
        adminService.deleteUser(userId);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "User deleted successfully";
    }
    else
    {
        response["message"] =
            "Failed to delete user";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void AdminController::deleteProduct(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    int productId)
{
    Json::Value response;

    bool success =
        adminService.deleteProduct(productId);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Product deleted successfully";
    }
    else
    {
        response["message"] =
            "Failed to delete product";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}