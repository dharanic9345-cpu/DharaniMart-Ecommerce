#pragma once

#include <string>

struct User
{
    int id = 0;
    std::string name;
    std::string email;
    std::string passwordHash;
    std::string role = "BUYER";
};