#pragma once

#include "Sensor.h"

class Device {
private:
    bool hasWifi;
    std::vector <Sensor*> repo;
public:
    Device();
    Device(bool wifi);
    void addSensor(Sensor* s);
    std::vector<Sensor*> getAllSensors();
    std::vector<Sensor*> getAlertingSensors();
    std::vector<Sensor*> FilterSensorsPrice(double price);
    void writeToFile(std::string filename, int price);

};


