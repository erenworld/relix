cmake_minimum_required(VERSION 3.14)       
project(RedisImplementation)                        

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    examples/client.cpp
    examples/server.cpp
)

add_executable(exec ${SOURCES})

