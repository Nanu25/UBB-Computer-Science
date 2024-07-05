cmake_minimum_required(VERSION 3.27)
project(oop_a4_5_Nanu25)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)

add_executable(oop_a4_5_Nanu25
        Domain/Movie.cpp
        Domain/Movie.h
        main.cpp
        DynamicArray/DynamicArray.cpp
        DynamicArray/DynamicArray.h
        Repository/Repository.cpp
        Repository/Repository.h
        UI/Ui.cpp
        UI/Ui.h
        Service/Service.cpp
        Service/Service.h
        Tests/tests.cpp
        Tests/tests.h)
