#include "HumiditySensor.h"

HumiditySensor::HumiditySensor(std::string producer, std::vector<double> reco) : Sensor(producer, reco) {

}

bool HumiditySensor::sendAlert() {
    int nr = 0;
    for(auto e : this->recordings)
        if(e < 30 || e > 85)
            nr++;
    return (nr >= 2);
}

double HumiditySensor::getPrice() {
    return 4;
}

std::string HumiditySensor::toString() {
    std::string reco = "";
    for(auto e : this->recordings)
        reco += std::to_string(e) + " ";

    std::string s = "Humidity Sensor: Producer " + this->producer + " recordings: " + reco + " price: " + std::to_string(this->getPrice());
    return s;
}

std::string HumiditySensor::getProducer() {
    return Sensor::getProducer();
}
