#pragma once

#include <string>
#include "Dwelling.h"

class Client {
protected:
    std::string name;
    double income;
public:
    //Client();
    //~Client();
    Client(std::string name, double income);
    virtual double totalIncome();
    virtual std::string toString();
    virtual bool isInterested(Dwelling x);
    std::string getName();
};


