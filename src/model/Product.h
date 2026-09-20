#pragma once

#include <string>

struct Product
{
    int id = 0;
    int sellerId = 0;

    std::string name;
    std::string description;
    double price = 0.0;
    int stock = 0;
    std::string category;
};