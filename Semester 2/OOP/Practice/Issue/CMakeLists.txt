cmake_minimum_required(VERSION 3.28)
project(TestProfa)

set(DCMAKE_PREFIX_PATH= "H:/qt_install/6.5.3/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(TestProfa main.cpp
        gui.cpp
        gui.h
        gui.ui
        Development.cpp
        Development.h
        Issue.cpp
        Issue.h
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        Observer.cpp
        Observer.h
        Tests.cpp
        Tests.h)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
