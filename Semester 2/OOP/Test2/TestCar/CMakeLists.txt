cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        Engine.cpp
        Engine.h
        ElectricEngine.cpp
        ElectricEngine.h
        TurboEngine.cpp
        TurboEngine.h
        Car.cpp
        Car.h
        Service.cpp
        Service.h
        Ui.cpp
        Ui.h)
