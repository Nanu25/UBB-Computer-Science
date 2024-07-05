
#include "Car.h"

double Car::computePrice() {
    if(this->bodyStyle == "Sedan")
        return this->eng->getPrice() + 8000;
    return this->eng->getPrice() + 9000;
}

std::string Car::toString() {
    std::string s = "Body style " + this->bodyStyle + " Car cost " + std::to_string(this->computePrice()) + this->eng->toString();
    return s;
}

Car::Car(std::string bodyStyle, std::string engineType, std::string fuelType, int autonomy) {
    this->bodyStyle = bodyStyle;

    if(engineType == "electric") {
        Engine* x = new ElectricEngine(fuelType, autonomy);
        this->eng = x;
    }else {
        Engine* x = new TurboEngine(fuelType);
        this->eng = x;
    }
}
