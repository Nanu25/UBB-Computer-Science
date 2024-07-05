#include "TurboEngine.h"

double TurboEngine::getPrice() {
    if(this->getFuelType() == "gasoline")
        return this->getBasePrice() + 0.01 * 100;
    return this->getBasePrice() + 0.01 * 150;
}

std::string TurboEngine::toString() {
    std::string s = "Fuel Type: " + this->getFuelType() + " base price: " + std::to_string(this->getBasePrice());
    return s;
}

TurboEngine::TurboEngine(std::string fuel) : Engine(fuel) {

}
