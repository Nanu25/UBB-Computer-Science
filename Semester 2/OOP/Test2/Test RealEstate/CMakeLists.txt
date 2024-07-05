cmake_minimum_required(VERSION 3.28)
project(Test_RealEstate)

set(CMAKE_CXX_STANDARD 26)

add_executable(Test_RealEstate main.cpp
        Client.cpp
        Client.h
        Dwelling.cpp
        Dwelling.h
        Person.cpp
        Person.h
        Company.cpp
        Company.h
        RealEstateAgency.cpp
        RealEstateAgency.h
        Ui.cpp
        Ui.h)
