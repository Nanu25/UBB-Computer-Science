#pragma once

#include <string>
#include <vector>

class Sensor {
protected:
    std::string producer;
    std::vector <double> recordings;
public:
    Sensor(std::string producer, std::vector<double> reco);
    virtual bool sendAlert();
    virtual double getPrice();
    virtual std::string toString();
    virtual std::string getProducer();

};


