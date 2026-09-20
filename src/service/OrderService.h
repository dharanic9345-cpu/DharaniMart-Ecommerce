#pragma once

#include "../model/Order.h"
#include "../repository/OrderRepository.h"
#include <vector>

class OrderService
{
private:
    OrderRepository orderRepository;

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