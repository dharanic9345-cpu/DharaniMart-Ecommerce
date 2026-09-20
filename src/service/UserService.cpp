#include "UserService.h"
#include <sodium.h>

bool UserService::registerUser(const User& user)
{
    if (sodium_init() < 0)
    {
        return false;
    }

    User newUser = user;

    char hashedPassword[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str(
            hashedPassword,
            user.passwordHash.c_str(),
            user.passwordHash.length(),
            crypto_pwhash_OPSLIMIT_INTERACTIVE,
            crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
    {
        return false;
    }

    newUser.passwordHash = hashedPassword;

    return userRepository.createUser(newUser);
}

User UserService::loginUser(const std::string& email, const std::string& password)
{
   User user = userRepository.findByEmail(email);

    if (user.id == 0)
    {
        return User{};
    }

    if (sodium_init() < 0)
    {
        return User{};
    }

    if (crypto_pwhash_str_verify(
            user.passwordHash.c_str(),
            password.c_str(),
            password.length()) != 0)
    {
        return User{};
    }

    return user;

}