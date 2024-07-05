#include "Engine.h"

Engine::Engine(std::string type) {
    this->fuelType = type;
    this->basePrice = 3000;
}

double Engine::getBasePrice() {
    return this->basePrice;
}

std::string Engine::getFuelType() {
    return this->fuelType;
}

double Engine::getPrice() {
    return this->basePrice;
}

std::string Engine::toString() {
    return "";
}
