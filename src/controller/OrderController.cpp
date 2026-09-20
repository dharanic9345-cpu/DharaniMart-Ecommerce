#include "OrderController.h"

void OrderController::createOrder(
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

    double totalAmount =
        (*json)["totalAmount"].asDouble();

    bool success =
        orderService.createOrder(
            buyerId,
            totalAmount);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Order created successfully";
    }
    else
    {
        response["message"] =
            "Failed to create order";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void OrderController::getOrdersByBuyer(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    int buyerId)
{
    Json::Value response;

    auto orders =
        orderService.getOrdersByBuyer(buyerId);

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


void OrderController::updatePaymentStatus(
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

    int orderId =
        (*json)["orderId"].asInt();

    std::string paymentStatus =
        (*json)["paymentStatus"].asString();

    bool success =
        orderService.updatePaymentStatus(
            orderId,
            paymentStatus);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Payment status updated";
    }
    else
    {
        response["message"] =
            "Payment status update failed";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}