
#include <fstream>
#include <algorithm>
#include "Service.h"

//Engine *Service::createEngine(std::string engineType, std::string fuelType, int autonomy) {
//    if(engineType == "electric") {
//        Engine* x = new ElectricEngine(fuelType, autonomy);
//        return x;
//    }
//    else {
//        Engine* x = new TurboEngine(fuelType);
//        return x;
//    }
//}

void Service::addCar(std::string bodyStyle, std::string engineType, std::string fuelType, int autonomy) {
    Car* car = new Car(bodyStyle, engineType, fuelType, autonomy);
    this->car_repo.push_back(car);
}

std::vector<Car *> Service::getCars() {
    return this->car_repo;
}

Service::Service() {
}

bool cmp(Car* c1, Car* c2) {
    return c1->computePrice()  < c2->computePrice();
}

std::vector<Car *> Service::getCarWithMaxPrice(double maxprice) {
    std::vector <Car*> aux;
    for(int i = 0; i < this->car_repo.size(); i++) {
        if(this->car_repo[i]->computePrice() <= maxprice)
            aux.push_back(this->car_repo[i]);
    }
    std::sort(aux.begin(), aux.end(), cmp);
    return aux;
}

void Service::writeToFile(std::string name, std::vector<Car *> cars) {
    std::ofstream g(name);
    for(auto e : cars)
        g << e->toString() << '\n';
    g.close();
}
