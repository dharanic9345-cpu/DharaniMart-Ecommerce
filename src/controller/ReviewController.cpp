#include "ReviewController.h"

void ReviewController::addReview(
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

    Review review;

    review.productId =
        (*json)["productId"].asInt();

    review.buyerId =
        (*json)["buyerId"].asInt();

    review.rating =
        (*json)["rating"].asInt();

    review.comment =
        (*json)["comment"].asString();

    bool success =
        reviewService.addReview(review);

    response["success"] = success;

    if (success)
    {
        response["message"] =
            "Review added successfully";
    }
    else
    {
        response["message"] =
            "Failed to add review";
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}


void ReviewController::getReviewsByProduct(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    int productId)
{
    Json::Value response;

    auto reviews =
        reviewService.getReviewsByProduct(productId);

    response["success"] = true;
    response["data"] = Json::arrayValue;

    for (const auto& review : reviews)
    {
        Json::Value data;

        data["id"] = review.id;
        data["productId"] = review.productId;
        data["buyerId"] = review.buyerId;
        data["rating"] = review.rating;
        data["comment"] = review.comment;

        response["data"].append(data);
    }

    callback(
        drogon::HttpResponse::newHttpJsonResponse(response));
}