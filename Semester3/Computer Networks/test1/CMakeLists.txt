cmake_minimum_required(VERSION 3.28)
project(test1 C)

set(CMAKE_C_STANDARD 11)

add_executable(test1 main.c)
target_link_libraries(test1 Ws2_32)
