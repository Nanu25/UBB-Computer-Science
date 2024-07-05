#pragma once

#include <string>

class Appliance {
protected:
    std::string id;
    double weight;
public:
    Appliance(std::string id, double w);
    virtual double consumedElectricity();
    virtual std::string toString();
    std::string getId();
};


