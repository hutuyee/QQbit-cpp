cmake_minimum_required(VERSION 3.15)

project(QQbit VERSION 1.0.0)

cmake_policy(SET CMP0167 OLD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

set(Boost_ROOT "D:/boost_1_85_0")
set(Boost_DIR "D:/boost_1_85_0/stage/lib/cmake/Boost-1.85.0")

find_package(Boost REQUIRED json system regex)
message("boost version:　${Boost_VERSION}")
message("boost include: ${Boost_INCLUDE_DIRS}")

set(OPENSSL_ROOT_DIR "D:/openssl-3.3.1")
find_package(OpenSSL REQUIRED)

message("openssl include:　${OPENSSL_INCLUDE_DIR}")

find_package(Lua REQUIRED)

message("lua include:　${LUA_INCLUDE_DIR} ")

configure_file(CMAKE.hpp.in cmake.hpp)


add_executable(QQbit ./src/main.cpp)

target_include_directories(QQbit PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(QQbit PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(QQbit PUBLIC ${OPENSSL_INCLUDE_DIR})
target_include_directories(QQbit PUBLIC ${LUA_INCLUDE_DIR})
target_include_directories(QQbit PUBLIC ${Boost_INCLUDE_DIRS})


target_link_libraries(QQbit PUBLIC Boost::json Boost::system Boost::regex)
target_link_libraries(QQbit PUBLIC ${LUA_LIBRARY})
target_link_libraries(QQbit PUBLIC Ws2_32)
target_link_libraries(QQbit PUBLIC OpenSSL::SSL OpenSSL::Crypto)

