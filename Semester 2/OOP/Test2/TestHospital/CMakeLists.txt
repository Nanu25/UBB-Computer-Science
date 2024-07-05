cmake_minimum_required(VERSION 3.28)
project(TestHospital)

set(CMAKE_CXX_STANDARD 20)

add_executable(TestHospital main.cpp
        HospitalDepartment.cpp
        HospitalDepartment.h
        NeonataUnit.cpp
        NeonataUnit.h
        Surgery.cpp
        Surgery.h
        Service.cpp
        Service.h
        Ui.cpp
        Ui.h)
