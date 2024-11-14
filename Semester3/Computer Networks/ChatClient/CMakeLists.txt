cmake_minimum_required(VERSION 3.28)
project(ChatClient C)

set(CMAKE_C_STANDARD 11)

add_executable(ChatClient main.c)
target_link_libraries(ChatClient Ws2_32)
