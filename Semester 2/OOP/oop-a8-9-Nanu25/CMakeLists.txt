cmake_minimum_required(VERSION 3.28)
project(oop_a8_9_Nanu25)
set(DCMAKE_PREFIX_PATH= "H:/qt_install/6.5.3/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6Widgets REQUIRED)

add_executable(oop_a8_9_Nanu25
        main.cpp
        Validator.cpp
        Domain/Movie.cpp
        Repository/CSVRepository.cpp
        Repository/FileRepository.cpp
        Repository/HTMLRepository.cpp
        Repository/Repository.cpp
        Service/Service.cpp
        Tests/tests.cpp
        UI/Ui.cpp
        UI/GUI.cpp
        UI/GUIWithDesigner.cpp
        UI/gui_user.h
        UI/gui_user.cpp)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)