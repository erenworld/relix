cmake_minimum_required(VERSION 3.14)       
project(RedisImplementation)                        

set(CMAKE_CXX_STANDARD 17)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

