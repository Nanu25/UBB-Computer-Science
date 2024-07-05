#pragma once

#include "Appliance.h"

class Refrigerator : public Appliance {
private:
    std::string electricityUsageClass;
    bool hasFreezer;
public:
    Refrigerator(std::string id, double w, std::string elec, bool freeze);
    double consumedElectricity() override;
    std::string toString() override;

};


