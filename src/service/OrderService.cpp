#include "OrderService.h"

bool OrderService::createOrder(
    int buyerId,
    double totalAmount)
{
    if (buyerId <= 0 || totalAmount < 0)
    {
        return false;
    }

    return orderRepository.createOrder(
        buyerId,
        totalAmount);
}


std::vector<Order>
OrderService::getOrdersByBuyer(int buyerId)
{
    if (buyerId <= 0)
    {
        return {};
    }

    return orderRepository.getOrdersByBuyer(
        buyerId);
}


bool OrderService::updatePaymentStatus(
    int orderId,
    const std::string& paymentStatus)
{
    if (orderId <= 0)
    {
        return false;
    }

    if (paymentStatus != "PENDING" &&
        paymentStatus != "PAID" &&
        paymentStatus != "FAILED")
    {
        return false;
    }

    return orderRepository.updatePaymentStatus(
        orderId,
        paymentStatus);
}