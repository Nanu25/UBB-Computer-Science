#pragma once

#include "Sensor.h"

class SmokeSensor : public Sensor {

public:
    SmokeSensor(std::string producer, std::vector<double> reco);
    bool sendAlert() override;
    double getPrice() override;
    std::string toString() override;
    std::string getProducer() override;
};


