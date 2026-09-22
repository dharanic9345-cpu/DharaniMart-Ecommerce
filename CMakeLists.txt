cmake_minimum_required(VERSION 3.25)

project(DharaniMart LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==============================
# Dependencies
# ==============================

find_package(Drogon CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)


# ==============================
# Main DharaniMart Application
# ==============================

add_executable(DharaniMart

    src/main.cpp

    # PostgreSQL
    src/repository/PostgreSQL/PostgreSQLConnection.cpp
    src/repository/PostgreSQL/PostgreSQLConnection.h
    src/repository/PostgreSQL/PostgreSQLUserRepository.cpp
    src/repository/PostgreSQL/PostgreSQLUserRepository.h

    # User
    src/repository/UserRepository.cpp
    src/service/UserService.cpp
    src/controller/UserController.cpp

    # Product
    src/repository/ProductRepository.cpp
    src/service/ProductService.cpp
    src/controller/ProductController.cpp

    # Cart
    src/repository/CartRepository.cpp
    src/service/CartService.cpp
    src/controller/CartController.cpp

    # Order
    src/repository/OrderRepository.cpp
    src/service/OrderService.cpp
    src/controller/OrderController.cpp

    # Review
    src/repository/ReviewRepository.cpp
    src/service/ReviewService.cpp
    src/controller/ReviewController.cpp

    # Admin
    src/repository/AdminRepository.cpp
    src/service/AdminService.cpp
    src/controller/AdminController.cpp

    # Chatbot
    src/service/ChatService.cpp
    src/controller/ChatController.cpp
)


target_link_libraries(DharaniMart
    PRIVATE

    Drogon::Drogon

    unofficial::sqlite3::sqlite3

    unofficial-sodium::sodium

    PostgreSQL::PostgreSQL
)


target_compile_features(DharaniMart
    PRIVATE
    cxx_std_20
)


# ==============================
# GoogleTest + GoogleMock
# ==============================

enable_testing()

add_executable(DharaniMartTests

    tests/test_main.cpp

    src/service/UserService.cpp
)


target_link_libraries(DharaniMartTests
    PRIVATE

    GTest::gmock_main

    Drogon::Drogon

    unofficial::sqlite3::sqlite3

    unofficial-sodium::sodium
)


target_compile_features(DharaniMartTests
    PRIVATE
    cxx_std_20
)


include(GoogleTest)

gtest_discover_tests(
    DharaniMartTests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


# ==============================
# SQLite Image Column Tool
# ==============================

add_executable(AddImageColumn

    tools/add_image_column.cpp
)


target_link_libraries(AddImageColumn
    PRIVATE

    unofficial::sqlite3::sqlite3
)


target_compile_features(AddImageColumn
    PRIVATE
    cxx_std_20
)


# ==============================
# PostgreSQL Connection Test
# ==============================

add_executable(PostgreSQLTest

    tools/postgres_test.cpp
)


target_link_libraries(PostgreSQLTest
    PRIVATE

    PostgreSQL::PostgreSQL
)


target_compile_features(PostgreSQLTest
    PRIVATE
    cxx_std_20
)


# ==============================
# PostgreSQL User Repository Test
# ==============================

add_executable(PostgreSQLUserTest

    tools/postgres_user_test.cpp

    src/repository/PostgreSQL/PostgreSQLConnection.cpp

    src/repository/PostgreSQL/PostgreSQLUserRepository.cpp
)


target_link_libraries(PostgreSQLUserTest
    PRIVATE

    PostgreSQL::PostgreSQL
)


target_compile_features(PostgreSQLUserTest
    PRIVATE
    cxx_std_20
)