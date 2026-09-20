#pragma once

#include "../service/OrderService.h"
#include <drogon/HttpController.h>

class OrderController
    : public drogon::HttpController<OrderController>
{
public:

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        OrderController::createOrder,
        "/api/v1/orders",
        drogon::Post);

    ADD_METHOD_TO(
        OrderController::getOrdersByBuyer,
        "/api/v1/orders/{1}",
        drogon::Get);

    ADD_METHOD_TO(
        OrderController::updatePaymentStatus,
        "/api/v1/orders/payment",
        drogon::Put);

    METHOD_LIST_END

    void createOrder(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

    void getOrdersByBuyer(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        int buyerId);

    void updatePaymentStatus(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

private:
    OrderService orderService;
};