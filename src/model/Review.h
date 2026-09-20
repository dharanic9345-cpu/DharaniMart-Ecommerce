#pragma once

#include <string>

struct Review
{
    int id = 0;
    int productId = 0;
    int buyerId = 0;
    int rating = 0;
    std::string comment;
};