#include "ReviewService.h"

bool ReviewService::addReview(const Review& review)
{
    if (review.productId <= 0 ||
        review.buyerId <= 0 ||
        review.rating < 1 ||
        review.rating > 5)
    {
        return false;
    }

    return reviewRepository.addReview(review);
}


std::vector<Review>
ReviewService::getReviewsByProduct(int productId)
{
    if (productId <= 0)
    {
        return {};
    }

    return reviewRepository.getReviewsByProduct(
        productId);
}