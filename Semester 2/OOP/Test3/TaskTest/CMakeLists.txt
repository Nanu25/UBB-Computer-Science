cmake_minimum_required(VERSION 3.28)
project(TaskTest)

set(DCMAKE_PREFIX_PATH= "H:/qt_install/6.5.3/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(TaskTest main.cpp
        Domain/Task.cpp
        Domain/Task.h
        Repository/Repository.cpp
        Repository/Repository.h
        Service/Service.cpp
        Service/Service.h
        GUI/Gui.cpp
        GUI/Gui.h
        GUI/Gui.ui)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
