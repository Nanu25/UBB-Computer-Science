#pragma once

#include "Client.h"

class Person: public Client {
public:
    //Person();
    //~Person();
    Person(std::string name, int income);
    bool isInterested(Dwelling x) override;
};


