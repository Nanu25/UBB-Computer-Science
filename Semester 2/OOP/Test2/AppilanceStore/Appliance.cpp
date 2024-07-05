#include "Appliance.h"

Appliance::Appliance(std::string id, double w) {
    this->id = id;
    this->weight = w;
}

double Appliance::consumedElectricity() {
    return 0;
}

std::string Appliance::toString() {
    return std::string();
}

std::string Appliance::getId() {
    return this->id;
}
