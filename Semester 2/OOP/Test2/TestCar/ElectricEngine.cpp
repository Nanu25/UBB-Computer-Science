
#include "ElectricEngine.h"

double ElectricEngine::getPrice() {
    return this->getBasePrice() + 0.01 * this->autonomy;
}

std::string ElectricEngine::toString() {
    std::string s = "Fuel Type: " + this->getFuelType() + " base price: " + std::to_string(this->getPrice()) + " autonomy: " + std::to_string(this->autonomy);
    return s;
}

ElectricEngine::ElectricEngine(std::string fuel, int autonomy) : Engine(fuel) {
    this->autonomy = autonomy;
}
