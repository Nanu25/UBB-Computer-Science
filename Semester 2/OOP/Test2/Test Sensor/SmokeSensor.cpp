#include "SmokeSensor.h"

SmokeSensor::SmokeSensor(std::string producer, std::vector<double> reco) : Sensor(producer, reco) {

}

bool SmokeSensor::sendAlert() {
    for(auto e : this->recordings)
        if(e > 1600)
            return 1;
    return 0;
}

double SmokeSensor::getPrice() {
    return 25;
}

std::string SmokeSensor::toString() {
    std::string reco = "";
    for(auto e : this->recordings)
        reco += std::to_string(e) + " ";

    std::string s = "Smoke Sensor: Producer " + this->producer + " recordings: " + reco + " price: " + std::to_string(this->getPrice());
    return s;
}

std::string SmokeSensor::getProducer() {
    return Sensor::getProducer();
}
