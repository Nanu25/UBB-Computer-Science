#include "Sensor.h"

Sensor::Sensor(std::string producer, std::vector<double> reco) {
    this->producer = producer;
    this->recordings = reco;
}

bool Sensor::sendAlert() {
    return false;
}

double Sensor::getPrice() {
    return 0;
}

std::string Sensor::toString() {
    return std::string();
}

std::string Sensor::getProducer() {
    return this->producer;
}
