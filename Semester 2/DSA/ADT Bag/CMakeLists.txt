cmake_minimum_required(VERSION 3.28)
project(ADT_Bag)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ADT_Bag
        App.cpp
        Bag.cpp
        Bag.h
        BagIterator.cpp
        BagIterator.h
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h)
