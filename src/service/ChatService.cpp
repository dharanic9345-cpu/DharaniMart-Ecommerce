#include "ChatService.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <drogon/drogon.h>
std::string ChatService::getResponse(const std::string& message)
{
    std::string lowerMessage = message;
    std::transform(
        lowerMessage.begin(),
        lowerMessage.end(),
        lowerMessage.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        }
    );
    if (lowerMessage.find("hello") != std::string::npos ||
        lowerMessage.find("hi") != std::string::npos)
    {
        return "Hello! Welcome to DharaniMart. How can I help you?";
    }
    if (lowerMessage.find("product") != std::string::npos)
    {
        return "I can help you with DharaniMart products, prices and product search.";
    }
    if (lowerMessage.find("cart") != std::string::npos)
    {
        return "You can add products to your cart and manage your shopping cart.";
    }
    if (lowerMessage.find("order") != std::string::npos)
    {
        return "You can check your order history and order details in DharaniMart.";
    }
    if (lowerMessage.find("payment") != std::string::npos)
    {
        return "DharaniMart currently supports mock payment confirmation for testing.";
    }
    if (lowerMessage.find("review") != std::string::npos ||
        lowerMessage.find("rating") != std::string::npos)
    {
        return "You can give ratings and reviews for products.";
    }
    return "I can help you with products, cart, orders, payments and reviews.";
}
