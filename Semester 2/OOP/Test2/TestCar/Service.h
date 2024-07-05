#pragma once

#include <vector>
#include "Car.h"

class Service {
private:
    std::vector <Car*> car_repo;
public:
    Service();
    //Engine* createEngine(std::string engineType, std::string fuelType, int autonomy);
    void addCar(std::string bodyStyle, std::string engineType, std::string fuelType, int autonomy);
    std::vector<Car*> getCars();
    std::vector<Car*> getCarWithMaxPrice(double maxprice);
    void writeToFile(std::string name, std::vector<Car*> cars);
};


