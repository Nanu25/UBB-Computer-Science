#include "Refrigerator.h"

Refrigerator::Refrigerator(std::string id, double w, std::string elec, bool freeze) : Appliance(id, w) {
    this->electricityUsageClass = elec;
    this->hasFreezer = freeze;
}

double Refrigerator::consumedElectricity() {
    double x;
    if(this->electricityUsageClass == "A")
        x = 3;
    else if(this->electricityUsageClass == "A+")
        x = 2.5;
    else x = 2;

    if(this->hasFreezer == 1)
        return x * 30 + 20;
    return x * 30;

}

std::string Refrigerator::toString() {
    std::string s = "Id: " + this->id + " Weight: " + std::to_string(this->weight) + " Electricity usage: " + this->electricityUsageClass + " has freezer: " + std::to_string(this->hasFreezer) + " Total consumed Electricity " + std::to_string(this->consumedElectricity());
    return s;
}
