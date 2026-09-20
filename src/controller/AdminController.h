#pragma once

#include "../service/AdminService.h"
#include <drogon/HttpController.h>

class AdminController
    : public drogon::HttpController<AdminController>
{
public:

    METHOD_LIST_BEGIN

    // View all users
    ADD_METHOD_TO(
        AdminController::getAllUsers,
        "/api/v1/admin/users",
        drogon::Get);

    // View all products
    ADD_METHOD_TO(
        AdminController::getAllProducts,
        "/api/v1/admin/products",
        drogon::Get);

    // View all orders
    ADD_METHOD_TO(
        AdminController::getAllOrders,
        "/api/v1/admin/orders",
        drogon::Get);

    // Delete user
    ADD_METHOD_TO(
        AdminController::deleteUser,
        "/api/v1/admin/users/{1}",
        drogon::Delete);

    // Delete product
    ADD_METHOD_TO(
        AdminController::deleteProduct,
        "/api/v1/admin/products/{1}",
        drogon::Delete);

    METHOD_LIST_END


    void getAllUsers(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);


    void getAllProducts(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);


    void getAllOrders(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);


    void deleteUser(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        int userId);


    void deleteProduct(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        int productId);


private:

    AdminService adminService;
};