#include <fstream>
#include "RealEstateAgency.h"

Dwelling *RealEstateAgency::addDwelling(double price, bool isProfitable) {
    Dwelling* x;
    x = new Dwelling(price, isProfitable);
    this->dwelling_repo.push_back(x);
    return x;
}

void RealEstateAgency::addClient(Client *c) {
    this->client_repo.push_back(c);
}

void RealEstateAgency::removeClient(std::string name) {
    for(int i = 0; i < this->client_repo.size(); i++)
        if(this->client_repo[i]->getName() == name)
            this->client_repo.erase(this->client_repo.begin() + i);
}

std::vector<Client *> RealEstateAgency::getInterestedClients(Dwelling x) {
    std::vector<Client*> aux;
    for(auto e : this->client_repo)
        if(e->isInterested(x))
            aux.push_back(e);
    return aux;
}

std::vector<Client *> RealEstateAgency::getClients() {
    return this->client_repo;
}

std::vector<Dwelling *> RealEstateAgency::getDwellings() {
    return this->dwelling_repo;
}

void RealEstateAgency::writeToFile(std::string s) {
    std::ofstream fout(s);
    for(auto e : this->client_repo)
        fout << e->toString() << '\n';
    fout.close();
}


