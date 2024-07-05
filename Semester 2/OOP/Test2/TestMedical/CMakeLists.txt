cmake_minimum_required(VERSION 3.28)
project(TestMedical)

set(CMAKE_CXX_STANDARD 17)

add_executable(TestMedical main.cpp
        MedicalAnalysis.cpp
        MedicalAnalysis.h
        BMI.cpp
        BMI.h
        BP.cpp
        BP.h
        Person.cpp
        Person.h
        Ui.cpp
        Ui.h)
