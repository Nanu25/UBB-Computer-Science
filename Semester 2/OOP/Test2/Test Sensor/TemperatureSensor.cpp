
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(std::string producer, std::vector<double> reco, double dia, double len) : Sensor(producer, reco) {
    this->diametre = dia;
    this->length = len;
}

bool TemperatureSensor::sendAlert() {
    int nr = 0;
    for(auto e : this->recordings)
        if(e > 35 || e < 10)
            nr++;
    return (nr >= 2);
}

double TemperatureSensor::getPrice() {
    if(this->diametre < 3 && this->length < 50)
        return 17;
    return 9;
}

std::string TemperatureSensor::toString() {
    std::string reco = "";
    for(auto e : this->recordings)
        reco += std::to_string(e) + " ";

    std::string s = "Temperature Sensor: Producer " + this->producer + " recordings: " + reco + " diameter: " + std::to_string(diametre) + " length: " + std::to_string(length) + " price: " + std::to_string(this->getPrice());
    return s;
}

std::string TemperatureSensor::getProducer() {
    return Sensor::getProducer();
}
