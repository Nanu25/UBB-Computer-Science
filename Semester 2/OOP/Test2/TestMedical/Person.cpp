#include <fstream>
#include "Person.h"

Person::Person(std::string name) {
    this->name = name;
}

void Person::addAnalysis(MedicalAnalysis *med) {
    this->repo.push_back(med);
}

std::vector<MedicalAnalysis *> Person::getAllAnalysis() {
    return this->repo;
}

Person::Person() {

}

std::vector<MedicalAnalysis *> Person::getAnalysisMonth(int month) {
    std::vector<MedicalAnalysis*> aux;
    for(auto e : this->repo) {
        int m = std::stoi(e->getDate().substr(5, 2));
        if(m == month)
            aux.push_back(e);
    }
    return aux;
}

bool Person::isIll(int month) {
    std::vector<MedicalAnalysis*> aux = this->getAnalysisMonth(month);
    bool ok = 0;
    if(aux.size() == 0)
        return  1;
    for(auto e : aux)
        if(e->isResultOK() == 1)
            ok = 1;
    return ok;
}

std::vector<MedicalAnalysis *> Person::getAnalysisDate(std::string s1, std::string s2) {
    std::vector<MedicalAnalysis*> aux;
    for(auto e : this->repo) {
        if(e->getDate() >= s1 && e->getDate()  <= s2)
            aux.push_back(e);
    }
    return aux;
}

void Person::writeToFile(std::string filename, std::string s1, std::string s2) {
    std::vector<MedicalAnalysis*> aux = this->getAnalysisDate(s1, s2);
    std::ofstream fout(filename);

    for(auto e : aux)
        fout << e->toString() << '\n';

    fout.close();
}
