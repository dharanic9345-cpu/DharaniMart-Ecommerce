#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/service/UserService.h"
#include "MockUserRepository.h"

using ::testing::_;
using ::testing::Return;


TEST(UserServiceMockTest, RegisterUserSuccessfully)
{
    MockUserRepository mockRepository;

    UserService service(mockRepository);

    User user;
    user.id = 0;
    user.name = "Mock User";
    user.email = "mockuser@gmail.com";
    user.passwordHash = "Test@123";
    user.role = "BUYER";

    EXPECT_CALL(
        mockRepository,
        createUser(_)
    )
    .WillOnce(Return(true));

    bool result = service.registerUser(user);

    EXPECT_TRUE(result);
}


TEST(UserServiceMockTest, RegisterUserFailsWhenRepositoryRejects)
{
    MockUserRepository mockRepository;

    UserService service(mockRepository);

    User user;
    user.id = 0;
    user.name = "Failed User";
    user.email = "faileduser@gmail.com";
    user.passwordHash = "Test@123";
    user.role = "BUYER";

    EXPECT_CALL(
        mockRepository,
        createUser(_)
    )
    .WillOnce(Return(false));

    bool result = service.registerUser(user);

    EXPECT_FALSE(result);
}


TEST(UserServiceMockTest, LoginWithWrongPasswordFails)
{
    MockUserRepository mockRepository;

    UserService service(mockRepository);

    User storedUser;
    storedUser.id = 1;
    storedUser.name = "Mock User";
    storedUser.email = "mockuser@gmail.com";
    storedUser.passwordHash = "invalid-hash";
    storedUser.role = "BUYER";

    EXPECT_CALL(
        mockRepository,
        findByEmail("mockuser@gmail.com")
    )
    .WillOnce(Return(storedUser));

    User result = service.loginUser(
        "mockuser@gmail.com",
        "WrongPassword"
    );

    EXPECT_EQ(result.id, 0);
}