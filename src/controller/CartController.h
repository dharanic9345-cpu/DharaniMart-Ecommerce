#pragma once

#include "../service/CartService.h"
#include <drogon/HttpController.h>

class CartController
    : public drogon::HttpController<CartController>
{
public:

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        CartController::addToCart,
        "/api/v1/cart/items",
        drogon::Post);

    ADD_METHOD_TO(
        CartController::getCartItems,
        "/api/v1/cart/{1}",
        drogon::Get);

    ADD_METHOD_TO(
        CartController::updateCartItem,
        "/api/v1/cart/items",
        drogon::Put);

    ADD_METHOD_TO(
        CartController::removeFromCart,
        "/api/v1/cart/items",
        drogon::Delete);

    ADD_METHOD_TO(
        CartController::clearCart,
        "/api/v1/cart/{1}",
        drogon::Delete);

    METHOD_LIST_END


    void addToCart(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);


    void getCartItems(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        int buyerId);


    void updateCartItem(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);


    void removeFromCart(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);


    void clearCart(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        int buyerId);


private:

    CartService cartService;
};