#pragma once

#include <string>
#include <vector>

struct OrderItem
{
    int id = 0;
    int orderId = 0;
    int productId = 0;
    int quantity = 0;
    double price = 0.0;
};

struct Order
{
    int id = 0;
    int buyerId = 0;
    double totalAmount = 0.0;
    std::string status = "PLACED";
    std::string paymentStatus = "PENDING";
};