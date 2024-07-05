//
// Created by alex_ on 4/23/2024.
//
#pragma once

#include <vector>
#include "Building.h"

class Service {
private:
    std::vector <Building*> repo;
public:
    Service();
    void addBuilding(Building *b);
    std::vector<Building*> getAllBuildings();
    std::vector<Building*> getAllToBeRestored();
    std::vector<Building*> getAllToBeRestoredGivenYear(std::vector<Building*> x, int year);
    std::vector<Building*> getAllToBeDemolished();
    void writeToFile(std::string filename, std::vector<Building*> x);

};


