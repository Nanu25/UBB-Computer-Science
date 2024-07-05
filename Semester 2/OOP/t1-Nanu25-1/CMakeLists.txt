cmake_minimum_required(VERSION 3.27)
project(t1_Nanu25_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(DynamicArray)

add_executable(t1_Nanu25_1
        DynamicArray/DynamicArray.cpp
        DynamicArray/DynamicArray.h
        main.cpp
        Domain/Domain.h
        Domain/Domain.cpp
        Repository/Repository.h
        Repository/Repository.cpp
        Service/Service.h
        Service/Service.cpp
        UI/Ui.h
        UI/Ui.cpp
        Tests/Test.h
        Tests/Test.cpp)
