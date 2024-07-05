cmake_minimum_required(VERSION 3.28)
project(AppilanceStore)

set(CMAKE_CXX_STANDARD 17)

add_executable(AppilanceStore main.cpp
        Appliance.h
        Appliance.cpp
        Refrigerator.cpp
        Refrigerator.h
        DishWasher.cpp
        DishWasher.h
        Service.cpp
        Service.h
        Ui.cpp
        Ui.h
)
