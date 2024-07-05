
#ifndef DELIVERNOW_REPOSITORY_H
#define DELIVERNOW_REPOSITORY_H


#include <vector>
#include "Courier.h"
#include "Package.h"

class Repository {
private:
    std::vector <Courier> courier_repo;
    std::vector <Package> package_repo;
public:
    void addCourier(Courier c);
    void addPackage(Package p);

    std::vector <Courier>& getCourrierRepo();
    std::vector <Package>& getPackageRepo();

    std::vector <std::string > getStreets();

    void readFile();
};


#endif //DELIVERNOW_REPOSITORY_H
