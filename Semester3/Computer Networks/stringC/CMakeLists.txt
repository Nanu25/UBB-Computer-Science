cmake_minimum_required(VERSION 3.28)
project(stringC C)

set(CMAKE_C_STANDARD 11)

add_executable(stringC main.c)
target_link_libraries(stringC Ws2_32)