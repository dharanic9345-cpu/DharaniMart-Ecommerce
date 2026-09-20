#pragma once

#include "../model/Review.h"
#include <vector>

class ReviewRepository
{
public:
    bool addReview(const Review& review);

    std::vector<Review> getReviewsByProduct(
        int productId);
};