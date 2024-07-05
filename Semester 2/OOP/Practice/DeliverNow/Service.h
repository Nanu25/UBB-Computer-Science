
#ifndef DELIVERNOW_SERVICE_H
#define DELIVERNOW_SERVICE_H


#include "Repository.h"
#include "Observer.h"

class Service : public Subject {
private:
    Repository& package_serv;

public:
    Service(Repository& repo);

    Repository& getServList();
    void addPackage(Package p);
    std::vector<std::string > getStreets();
};


#endif //DELIVERNOW_SERVICE_H
