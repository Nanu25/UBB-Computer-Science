cmake_minimum_required(VERSION 3.28)
project(oop_e_912_914_Nanu25)

set(DCMAKE_PREFIX_PATH= "H:/qt_install/6.5.3/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(oop_e_912_914_Nanu25
        main.cpp
        Researcher.h
        Researcher.cpp
        Repository.h
        Repository.cpp
        Service.h
        Service.cpp
        Service.cpp
        gui.h
        Ideea.cpp
        gui.cpp
        Observer.h
        Observer.cpp)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
