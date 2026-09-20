#include "AdminService.h"

std::vector<User> AdminService::getAllUsers()
{
    return adminRepository.getAllUsers();
}
std::vector<Product> AdminService::getAllProducts()
{
    return adminRepository.getAllProducts();
}
std::vector<Order> AdminService::getAllOrders()
{
    return adminRepository.getAllOrders();
}
bool AdminService::deleteUser(int userId)
{
    if (userId <= 0)
    {
        return false;
    }

    return adminRepository.deleteUser(userId);
}
bool AdminService::deleteProduct(int productId)
{
    if (productId <= 0)
    {
        return false;
    }

    return adminRepository.deleteProduct(productId);
}