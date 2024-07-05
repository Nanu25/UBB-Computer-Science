#include <fstream>
#include <algorithm>
#include "Service.h"

Service::Service() {

}

void Service::addAppliance(Appliance *x) {
    this->repo.push_back(x);
}

std::vector<Appliance *> Service::getAllAppliances() {
    return this->repo;
}

std::vector<Appliance *> Service::getAllWithConsumedElectricityLessThan(double maxElectricity) {
    std::vector <Appliance*> aux;
    for(auto e : this->repo)
        if(e->consumedElectricity() <= maxElectricity)
            aux.push_back(e);
    return aux;
}

std::vector<Appliance *> Service::getAllWithConsumedElectricityMoreThan(double maxElectricity) {
    std::vector <Appliance*> aux;
    for(auto e : this->repo)
        if(e->consumedElectricity() >= maxElectricity)
            aux.push_back(e);
    return aux;
}

void Service::writeToFile(std::string filename, double maxElec) {
    std::vector <Appliance*> aux = this->getAllWithConsumedElectricityMoreThan(maxElec);
    aux = this->sortById(aux);
    std::ofstream fout(filename);
    for(auto e : aux)
        fout << e->toString() << '\n';
    fout.close();
}

bool cmp(Appliance* a1, Appliance* a2) {
    return a1->getId() < a2->getId();
}

std::vector<Appliance *> Service::sortById(std::vector<Appliance *> aux) {
    std::sort(aux.begin(), aux.end(), cmp);
    return aux;
}

