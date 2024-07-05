#pragma once
#include "Engine.h"

class ElectricEngine : public Engine{
private:
    int autonomy;
public:
    ElectricEngine(std::string fuel, int autonomy);
    double getPrice() override;
    std::string toString() override;
};


