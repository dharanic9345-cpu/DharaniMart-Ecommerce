cmake_minimum_required(VERSION 3.25)

project(DharaniMart LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)

add_executable(DharaniMart
    src/main.cpp

    src/repository/UserRepository.cpp
    src/service/UserService.cpp
    src/controller/UserController.cpp

    src/repository/ProductRepository.cpp
    src/service/ProductService.cpp
    src/controller/ProductController.cpp

    src/repository/CartRepository.cpp
    src/service/CartService.cpp
    src/controller/CartController.cpp

    src/repository/OrderRepository.cpp
    src/service/OrderService.cpp
    src/controller/OrderController.cpp

    src/repository/ReviewRepository.cpp
    src/service/ReviewService.cpp
    src/controller/ReviewController.cpp
    src/repository/AdminRepository.cpp
    src/service/AdminService.cpp
     src/controller/AdminController.cpp
)

target_link_libraries(DharaniMart
    PRIVATE
    Drogon::Drogon
    unofficial::sqlite3::sqlite3
    unofficial-sodium::sodium
)

target_compile_features(DharaniMart PRIVATE cxx_std_20)