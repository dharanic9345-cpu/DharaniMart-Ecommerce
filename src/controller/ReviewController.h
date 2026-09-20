#pragma once

#include "../service/ReviewService.h"
#include <drogon/HttpController.h>

class ReviewController
    : public drogon::HttpController<ReviewController>
{
public:

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        ReviewController::addReview,
        "/api/v1/reviews",
        drogon::Post);

    ADD_METHOD_TO(
        ReviewController::getReviewsByProduct,
        "/api/v1/reviews/{1}",
        drogon::Get);

    METHOD_LIST_END

    void addReview(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

    void getReviewsByProduct(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        int productId);

private:
    ReviewService reviewService;
};