cmake_minimum_required(VERSION 3.28)
project(ChatServer C)

set(CMAKE_C_STANDARD 11)

add_executable(ChatServer main.c)
target_link_libraries(ChatServer Ws2_32)
