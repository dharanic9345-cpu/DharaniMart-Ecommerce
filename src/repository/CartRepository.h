#pragma once

#include "../model/Cart.h"
#include <vector>

class CartRepository
{
public:
    bool addToCart(int buyerId, int productId, int quantity);

    std::vector<CartItem> getCartItems(int buyerId);

    bool updateCartItem(
        int buyerId,
        int productId,
        int quantity);

    bool removeFromCart(
        int buyerId,
        int productId);

    bool clearCart(int buyerId);
};