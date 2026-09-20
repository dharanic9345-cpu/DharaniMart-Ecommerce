#pragma once

#include "../model/Order.h"
#include <vector>

class OrderRepository
{
public:
    bool createOrder(
        int buyerId,
        double totalAmount);

    std::vector<Order> getOrdersByBuyer(
        int buyerId);

    bool updatePaymentStatus(
        int orderId,
        const std::string& paymentStatus);
};