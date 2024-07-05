
#include <algorithm>
#include <fstream>
#include "Service.h"

void Service::addDepartment(HospitalDepartment *x) {
    this->repo.push_back(x);
}

std::vector<HospitalDepartment *> Service::getAllDepartment() {
    return this->repo;
}

Service::Service() {

}

std::vector<HospitalDepartment *> Service::getAllEfficientDepartments() {
    std::vector <HospitalDepartment*> aux;
    for(auto e : this->repo)
        if(e->isEfficient() == 1)
            aux.push_back(e);
    return aux;
}

bool cmp(HospitalDepartment* h1, HospitalDepartment* h2) {
    return h1->getName() <= h2->getName();
}

std::vector<HospitalDepartment *> Service::SortAllDepartment() {
    std::vector <HospitalDepartment*> aux;
    for(auto e : this->repo)
        aux.push_back(e);

    std::sort(aux.begin(), aux.end(), cmp);
    return  aux;
}

void Service::writeToFile(std::string filename) {
    std::vector <HospitalDepartment*> aux = this->SortAllDepartment();

    std::ofstream fout(filename);

    for(auto e : aux)
        fout << e->toString() << '\n';
    fout.close();
}
