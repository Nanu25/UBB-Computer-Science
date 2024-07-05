cmake_minimum_required(VERSION 3.27)
project(a2_3_Nanu25 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(a2_3_Nanu25
        Domain/domain.c
        Domain/domain.h
        main.c
        Repository/repository.c
        Repository/repository.h
        Service/service.c
        Service/service.h
        DynamicArray/Dynamic_array.c
        Ui.c
        Ui.c
        Tests/Test.c
        Tests/Test.h)
