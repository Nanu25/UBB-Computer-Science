
#include "Service.h"

Service::Service(Repository &repo) : package_serv{repo}{

}

Repository &Service::getServList() {
    return this->package_serv;
}

void Service::addPackage(Package p) {
    this->package_serv.addPackage(p);
    this->notify();
}

std::vector<std::string> Service::getStreets() {
    return this->package_serv.getStreets();
}
