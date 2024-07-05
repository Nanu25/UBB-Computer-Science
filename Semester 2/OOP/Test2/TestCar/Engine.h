#pragma once

#include <string>

class Engine {
private:
     std::string fuelType;
     double basePrice;
public:
    Engine(std::string type);
    virtual double getPrice();
    virtual std::string toString();
    double getBasePrice();
    std::string getFuelType();
};


