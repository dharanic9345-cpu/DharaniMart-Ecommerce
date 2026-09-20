#include "CartController.h"

void CartController::addToCart(
    const drogon::HttpRequestPtr& request,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    auto json = request->getJsonObject();

    if (!json)
    {
        response["success"] = false;
        response["message"] = "Invalid JSON";

        callback(
            drogon::HttpResponse::newHttpJsonResponse(response));

        return;
    }

    int buyerId =
        (*json)["buyerId"].asInt();

    int productId =
        (*json)["productId"].asInt();

    int quantity =
        (*json)["quantity"].asInt();

    bool success =
        cartService.addToCart(
            buyerId,
            productId,
            quantity);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Product added to cart";
    }
    else
    {
        response["message"] =
            "Failed to add product to cart";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void CartController::getCartItems(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    int buyerId)
{
    Json::Value response;

    auto items =
        cartService.getCartItems(buyerId);

    response["success"] = true;
    response["data"] = Json::arrayValue;

    for (const auto& item : items)
    {
        Json::Value data;

        data["id"] = item.id;
        data["cartId"] = item.cartId;
        data["productId"] = item.productId;
        data["quantity"] = item.quantity;

        response["data"].append(data);
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void CartController::updateCartItem(
    const drogon::HttpRequestPtr& request,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    auto json = request->getJsonObject();

    if (!json)
    {
        response["success"] = false;
        response["message"] = "Invalid JSON";

        callback(
            drogon::HttpResponse::newHttpJsonResponse(response));

        return;
    }

    int buyerId =
        (*json)["buyerId"].asInt();

    int productId =
        (*json)["productId"].asInt();

    int quantity =
        (*json)["quantity"].asInt();

    bool success =
        cartService.updateCartItem(
            buyerId,
            productId,
            quantity);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Cart quantity updated";
    }
    else
    {
        response["message"] =
            "Cart update failed";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void CartController::removeFromCart(
    const drogon::HttpRequestPtr& request,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    auto json = request->getJsonObject();

    if (!json)
    {
        response["success"] = false;
        response["message"] = "Invalid JSON";

        callback(
            drogon::HttpResponse::newHttpJsonResponse(response));

        return;
    }

    int buyerId =
        (*json)["buyerId"].asInt();

    int productId =
        (*json)["productId"].asInt();

    bool success =
        cartService.removeFromCart(
            buyerId,
            productId);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Product removed from cart";
    }
    else
    {
        response["message"] =
            "Failed to remove product";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void CartController::clearCart(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    int buyerId)
{
    Json::Value response;

    bool success =
        cartService.clearCart(buyerId);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Cart cleared successfully";
    }
    else
    {
        response["message"] =
            "Failed to clear cart";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}