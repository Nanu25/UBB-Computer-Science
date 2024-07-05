#pragma once

#include <vector>
#include "Client.h"

class RealEstateAgency {
private:
    std::vector <Client*> client_repo;
    std::vector <Dwelling*> dwelling_repo;
public:
    Dwelling* addDwelling(double price, bool isProfitable);
    void addClient(Client* c);
    void removeClient(std::string name);
    std::vector<Client*> getInterestedClients(Dwelling x);
    std::vector<Client*> getClients();
    std::vector<Dwelling*> getDwellings();
    void writeToFile(std::string s);

};


