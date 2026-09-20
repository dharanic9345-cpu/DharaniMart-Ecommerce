#pragma once

#include "../model/User.h"
#include "../model/Product.h"
#include "../model/Order.h"
#include "../repository/AdminRepository.h"
#include <vector>

class AdminService
{
private:
    AdminRepository adminRepository;

public:
    std::vector<User> getAllUsers();

    std::vector<Product> getAllProducts();

    std::vector<Order> getAllOrders();
    bool deleteUser(int userId);
    bool deleteProduct(int productId);
};