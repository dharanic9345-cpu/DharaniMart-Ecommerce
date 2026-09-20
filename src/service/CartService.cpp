#include "CartService.h"

bool CartService::addToCart(
    int buyerId,
    int productId,
    int quantity)
{
    if (buyerId <= 0 ||
        productId <= 0 ||
        quantity <= 0)
    {
        return false;
    }

    return cartRepository.addToCart(
        buyerId,
        productId,
        quantity);
}


std::vector<CartItem>
CartService::getCartItems(int buyerId)
{
    if (buyerId <= 0)
    {
        return {};
    }

    return cartRepository.getCartItems(buyerId);
}


bool CartService::updateCartItem(
    int buyerId,
    int productId,
    int quantity)
{
    if (buyerId <= 0 ||
        productId <= 0 ||
        quantity <= 0)
    {
        return false;
    }

    return cartRepository.updateCartItem(
        buyerId,
        productId,
        quantity);
}


bool CartService::removeFromCart(
    int buyerId,
    int productId)
{
    if (buyerId <= 0 ||
        productId <= 0)
    {
        return false;
    }

    return cartRepository.removeFromCart(
        buyerId,
        productId);
}


bool CartService::clearCart(int buyerId)
{
    if (buyerId <= 0)
    {
        return false;
    }

    return cartRepository.clearCart(buyerId);
}