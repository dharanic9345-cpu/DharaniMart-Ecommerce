#include "ProductService.h"

bool ProductService::addProduct(const Product& product)
{
    if (product.name.empty())
    {
        return false;
    }

    if (product.price < 0)
    {
        return false;
    }

    if (product.stock < 0)
    {
        return false;
    }

    if (product.sellerId <= 0)
    {
        return false;
    }

    return productRepository.createProduct(product);
}


std::vector<Product>
ProductService::getSellerProducts(int sellerId)
{
    if (sellerId <= 0)
    {
        return {};
    }

    return productRepository.getProductsBySeller(sellerId);
}


std::vector<Product>
ProductService::getAllProducts()
{
    return productRepository.getAllProducts();
}


// SEARCH + CATEGORY FILTER
std::vector<Product>
ProductService::searchProducts(
    const std::string& keyword,
    const std::string& category)
{
    return productRepository.searchProducts(
        keyword,
        category);
}


bool ProductService::updateProduct(
    const Product& product)
{
    if (product.id <= 0)
    {
        return false;
    }

    if (product.sellerId <= 0)
    {
        return false;
    }

    if (product.name.empty())
    {
        return false;
    }

    if (product.price < 0 ||
        product.stock < 0)
    {
        return false;
    }

    return productRepository.updateProduct(product);
}


bool ProductService::deleteProduct(
    int productId,
    int sellerId)
{
    if (productId <= 0 ||
        sellerId <= 0)
    {
        return false;
    }

    return productRepository.deleteProduct(
        productId,
        sellerId);
}