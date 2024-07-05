cmake_minimum_required(VERSION 3.28)
project(SearchEngine)

set(DCMAKE_PREFIX_PATH= "H:/qt_install/6.5.3/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6Widgets REQUIRED)


set(CMAKE_CXX_STANDARD 17)

add_executable(SearchEngine main.cpp
        Gui/Gui.cpp
        Gui/Gui.h
        Gui/Gui.ui
        Domain/Document.cpp
        Domain/Document.h
        Repository/Repository.cpp
        Repository/Repository.h
        Service/Service.cpp
        Service/Service.h)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)