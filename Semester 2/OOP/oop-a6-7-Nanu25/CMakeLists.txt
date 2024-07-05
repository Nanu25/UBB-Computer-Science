cmake_minimum_required(VERSION 3.27)
project(oop_a6_7_Nanu25)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)
include_directories(DynamicArray)
include_directories(Repository)
include_directories(Service)
include_directories(Tests)
include_directories(UI)

add_executable(oop_a6_7_Nanu25
        Domain/Movie.cpp
        Domain/Movie.h
        DynamicArray/DynamicArray.h
        Repository/Repository.cpp
        Repository/Repository.h
        Service/Service.cpp
        Service/Service.h
        Tests/tests.cpp
        Tests/tests.h
        UI/Ui.cpp
        UI/Ui.h
        main.cpp
        Repository/FileRepository.cpp
        Repository/FileRepository.h
        Repository/CSVRepository.cpp
        Repository/CSVRepository.h
        Validator.cpp
        Validator.h
        Repository/HTMLRepository.cpp
        Repository/HTMLRepository.h
)
