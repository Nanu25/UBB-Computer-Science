cmake_minimum_required(VERSION 3.28)
project(oop-a10-Nanu25)
set(DCMAKE_PREFIX_PATH= "H:/qt_install/6.5.3/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6Widgets REQUIRED)

add_executable(oop-a10-Nanu25
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
        UI/gui_user.cpp
        Undo_Redo/UndoRedo.cpp
        Undo_Redo/UndoRedo.h
        Undo_Redo/UndoRedo.h
        Undo_Redo/UndoRedo.cpp
        UI/GUIWithDesigner.cpp
        UI/GUIWithDesigner.cpp
        Undo_Redo/UndoRedo.h
        UI/GUIWithDesigner.h
        UI/GUIWithDesigner.h
        UI/gui_user.h
        UI/gui_user.h
        UI/gui_user.h
        Domain/Movie.h
        UI/gui_user.cpp
        UI/gui_user.cpp
        Observer.h
        Observer.h
        Service/Service.h
        UI/gui_user.h
        UI/gui_user.h
        Observer.cpp)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)