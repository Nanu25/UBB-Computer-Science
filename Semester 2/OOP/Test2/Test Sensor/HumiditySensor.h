#pragma once

#include <string>
#include <vector>
#include "Sensor.h"

class HumiditySensor : public Sensor {
public:
    HumiditySensor(std::string producer, std::vector<double> reco);
    bool sendAlert() override;
    double getPrice() override;
    std::string toString() override;
    std::string getProducer() override;

};


