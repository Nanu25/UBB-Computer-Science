cmake_minimum_required(VERSION 3.28)
project(Test_Sensor)

set(CMAKE_CXX_STANDARD 17)

add_executable(Test_Sensor main.cpp
        Sensor.cpp
        Sensor.h
        TemperatureSensor.cpp
        TemperatureSensor.h
        HumiditySensor.cpp
        HumiditySensor.h
        SmokeSensor.cpp
        SmokeSensor.h
        Device.cpp
        Device.h
        Ui.cpp
        Ui.h)
