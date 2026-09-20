#pragma once

#include "../model/Product.h"
#include "../repository/ProductRepository.h"
#include <vector>
#include <string>

class ProductService
{
private:
    ProductRepository productRepository;

public:
    bool addProduct(const Product& product);

    std::vector<Product> getSellerProducts(int sellerId);

    std::vector<Product> getAllProducts();

    std::vector<Product> searchProducts(
        const std::string& keyword,
        const std::string& category);

    bool updateProduct(const Product& product);

    bool deleteProduct(
        int productId,
        int sellerId);
};