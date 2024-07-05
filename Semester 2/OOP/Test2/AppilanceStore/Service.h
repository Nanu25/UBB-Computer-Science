#pragma once

#include <vector>
#include "Appliance.h"

class Service {
private:
    std::vector <Appliance*> repo;
    std::vector<Appliance*> sortById(std::vector<Appliance*> aux);
public:
    Service();
    void addAppliance(Appliance* x);
    std::vector<Appliance*> getAllAppliances();
    std::vector<Appliance*> getAllWithConsumedElectricityLessThan(double maxElectricity);
    std::vector<Appliance*> getAllWithConsumedElectricityMoreThan(double maxElectricity);
    void writeToFile(std::string filename, double maxElec);
};



