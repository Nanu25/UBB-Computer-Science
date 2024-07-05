cmake_minimum_required(VERSION 3.28)
project(DeliverNow)

set(DCMAKE_PREFIX_PATH= "H:/qt_install/6.5.3/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6Widgets REQUIRED)


set(CMAKE_CXX_STANDARD 17)

add_executable(DeliverNow main.cpp
        Courier.cpp
        Courier.h
        Package.cpp
        Package.h
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        gui.cpp
        gui.h
        gui.ui
        Observer.cpp
        Observer.h)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
