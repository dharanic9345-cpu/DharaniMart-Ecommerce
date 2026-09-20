#pragma once

#include "../service/ProductService.h"
#include <drogon/HttpController.h>

class ProductController
    : public drogon::HttpController<ProductController>
{
public:

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        ProductController::addProduct,
        "/api/v1/products",
        drogon::Post);

    ADD_METHOD_TO(
        ProductController::getAllProducts,
        "/api/v1/products",
        drogon::Get);

    ADD_METHOD_TO(
        ProductController::searchProducts,
        "/api/v1/products/search",
        drogon::Get);

    ADD_METHOD_TO(
        ProductController::getSellerProducts,
        "/api/v1/products/seller/{1}",
        drogon::Get);

    ADD_METHOD_TO(
        ProductController::updateProduct,
        "/api/v1/products/{1}",
        drogon::Put);

    ADD_METHOD_TO(
        ProductController::deleteProduct,
        "/api/v1/products/{1}",
        drogon::Delete);

    METHOD_LIST_END


    void addProduct(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);


    void getAllProducts(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);


    void searchProducts(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);


    void getSellerProducts(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        int sellerId);


    void updateProduct(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        int productId);


    void deleteProduct(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        int productId);


private:

    ProductService productService;
};