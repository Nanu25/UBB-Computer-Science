#include <algorithm>
#include <fstream>
#include "Device.h"

Device::Device(bool wifi) {
    this->hasWifi = wifi;
}

void Device::addSensor(Sensor *s) {
    this->repo.push_back(s);
}

std::vector<Sensor *> Device::getAllSensors() {
    return this->repo;
}

Device::Device() {

}

std::vector<Sensor *> Device::getAlertingSensors() {
    std::vector <Sensor*> aux;
    for(auto e : this->repo)
        if(e->sendAlert() == 1)
            aux.push_back(e);
    return aux;
}

bool cmp(Sensor* s1, Sensor* s2) {
    return s1->getProducer() < s2->getProducer();
}

std::vector<Sensor *> Device::FilterSensorsPrice(double price) {
    std::vector <Sensor*> aux;
    for(auto e : this->repo)
        if(e->getPrice() < price)
            aux.push_back(e);

//    for(int i = 0; i < aux.size(); i++)
//        for(int j = i; j < aux.size(); j++)
//            if(aux[i]->getProducer() > aux[j]->getProducer())
//                std::swap(aux[i], aux[j]);

    sort(aux.begin(), aux.end(), cmp);
    return aux;
}

void Device::writeToFile(std::string filename, int price) {
    std::vector <Sensor*> aux = this->FilterSensorsPrice(price);
    std::ofstream fout(filename);
    for(auto e : aux)
        fout << e->toString() << '\n';
    fout.close();
}
