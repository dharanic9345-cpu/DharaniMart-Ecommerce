#include "ProductController.h"

void ProductController::addProduct(
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

    Product product;

    product.sellerId =
        (*json)["sellerId"].asInt();

    product.name =
        (*json)["name"].asString();

    product.description =
        (*json)["description"].asString();

    product.price =
        (*json)["price"].asDouble();

    product.stock =
        (*json)["stock"].asInt();

    product.category =
        (*json)["category"].asString();

    bool success =
        productService.addProduct(product);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Product added successfully";
    }
    else
    {
        response["message"] =
            "Product creation failed";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void ProductController::getAllProducts(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    auto products =
        productService.getAllProducts();

    response["success"] = true;
    response["data"] = Json::arrayValue;

    for (const auto& product : products)
    {
        Json::Value item;

        item["id"] = product.id;
        item["sellerId"] = product.sellerId;
        item["name"] = product.name;
        item["description"] = product.description;
        item["price"] = product.price;
        item["stock"] = product.stock;
        item["category"] = product.category;

        response["data"].append(item);
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


// SEARCH + CATEGORY FILTER
void ProductController::searchProducts(
    const drogon::HttpRequestPtr& request,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    std::string keyword =
        request->getParameter("keyword");

    std::string category =
        request->getParameter("category");

    auto products =
        productService.searchProducts(
            keyword,
            category);

    response["success"] = true;
    response["data"] = Json::arrayValue;

    for (const auto& product : products)
    {
        Json::Value item;

        item["id"] = product.id;
        item["sellerId"] = product.sellerId;
        item["name"] = product.name;
        item["description"] = product.description;
        item["price"] = product.price;
        item["stock"] = product.stock;
        item["category"] = product.category;

        response["data"].append(item);
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void ProductController::getSellerProducts(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    int sellerId)
{
    Json::Value response;

    auto products =
        productService.getSellerProducts(sellerId);

    response["success"] = true;
    response["data"] = Json::arrayValue;

    for (const auto& product : products)
    {
        Json::Value item;

        item["id"] = product.id;
        item["sellerId"] = product.sellerId;
        item["name"] = product.name;
        item["description"] = product.description;
        item["price"] = product.price;
        item["stock"] = product.stock;
        item["category"] = product.category;

        response["data"].append(item);
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void ProductController::updateProduct(
    const drogon::HttpRequestPtr& request,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    int productId)
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

    Product product;

    product.id = productId;

    product.sellerId =
        (*json)["sellerId"].asInt();

    product.name =
        (*json)["name"].asString();

    product.description =
        (*json)["description"].asString();

    product.price =
        (*json)["price"].asDouble();

    product.stock =
        (*json)["stock"].asInt();

    product.category =
        (*json)["category"].asString();

    bool success =
        productService.updateProduct(product);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Product updated successfully";
    }
    else
    {
        response["message"] =
            "Product update failed";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void ProductController::deleteProduct(
    const drogon::HttpRequestPtr& request,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    int productId)
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

    int sellerId =
        (*json)["sellerId"].asInt();

    bool success =
        productService.deleteProduct(
            productId,
            sellerId);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Product deleted successfully";
    }
    else
    {
        response["message"] =
            "Product deletion failed";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}