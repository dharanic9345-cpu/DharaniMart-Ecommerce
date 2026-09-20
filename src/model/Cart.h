#pragma once

#include <string>

struct CartItem
{
    int id = 0;
    int cartId = 0;
    int productId = 0;
    int quantity = 0;
};

struct Cart
{
    int id = 0;
    int buyerId = 0;
};