#pragma once

#include "../model/Review.h"
#include "../repository/ReviewRepository.h"
#include <vector>

class ReviewService
{
private:
    ReviewRepository reviewRepository;

public:
    bool addReview(const Review& review);

    std::vector<Review> getReviewsByProduct(
        int productId);
};