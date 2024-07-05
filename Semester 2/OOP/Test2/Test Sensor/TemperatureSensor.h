#pragma once

#include "Sensor.h"

class TemperatureSensor : public Sensor {
private:
    double diametre, length;
public:
    TemperatureSensor(std::string producer, std::vector<double> reco, double dia, double len);
    bool sendAlert() override;
    double getPrice() override;
    std::string toString() override;
    std::string getProducer() override;
};


