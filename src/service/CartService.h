#pragma once

#include "../model/Cart.h"
#include "../repository/CartRepository.h"
#include <vector>

class CartService
{
private:
    CartRepository cartRepository;

public:
    bool addToCart(
        int buyerId,
        int productId,
        int quantity);

    std::vector<CartItem> getCartItems(
        int buyerId);

    bool updateCartItem(
        int buyerId,
        int productId,
        int quantity);

    bool removeFromCart(
        int buyerId,
        int productId);

    bool clearCart(
        int buyerId);
};