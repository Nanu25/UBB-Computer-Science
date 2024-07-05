#pragma once

#include "Appliance.h"

class DishWasher : public Appliance {
private:
    double washingCycleLength, consumeEnergyForOneHour;
public:
    DishWasher(std::string id, double w, double wash, double consume);
    double consumedElectricity() override;
    std::string toString() override;
};


