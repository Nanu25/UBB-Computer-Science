
#include "DishWasher.h"

DishWasher::DishWasher(std::string id, double w, double wash, double consume) : Appliance(id, w) {
    this->washingCycleLength = wash;
    this->consumeEnergyForOneHour = consume;
}

double DishWasher::consumedElectricity() {
    return this->washingCycleLength / this->consumeEnergyForOneHour * 20;
}

std::string DishWasher::toString() {
    std::string s = "Id: " + this->id + " Weight: " + std::to_string(this->weight) + " Washing Cycle Lenght: " + std::to_string(this->washingCycleLength) + " consumed electricity for one hour " + std::to_string(this->consumeEnergyForOneHour) + " Total consumed Electricity " + std::to_string(this->consumedElectricity());
    return s;
}
