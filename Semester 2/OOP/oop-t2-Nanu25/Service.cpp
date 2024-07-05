//
// Created by alex_ on 4/23/2024.
//

#include <fstream>
#include "Service.h"

Service::Service() {

}

void Service::addBuilding(Building *b) {
    this->repo.push_back(b);
}

std::vector<Building *> Service::getAllBuildings() {
    return this->repo;
}

std::vector<Building *> Service::getAllToBeRestored() {
    std::vector<Building*> aux;
    for(auto e : this->repo)
        if(e->mustBeRestored() == 1)
            aux.push_back(e);
    return aux;
}

std::vector<Building *> Service::getAllToBeRestoredGivenYear(std::vector<Building*> x, int year) {
    std::vector<Building*> aux;
    for(auto e : x)
        if(e->getYear() == year)
            aux.push_back(e);
    return aux;
}

std::vector<Building *> Service::getAllToBeDemolished() {
    std::vector<Building*> aux;
    for(auto e : this->repo)
        if(e->canBeDemolished() == 1)
            aux.push_back(e);
    return aux;
}

void Service::writeToFile(std::string filename, std::vector<Building *> x) {
    std::ofstream fout(filename);
    for(auto e : x)
        fout << e->toString() << '\n';
    fout.close();
}
