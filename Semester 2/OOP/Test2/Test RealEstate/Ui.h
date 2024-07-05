#pragma once

#include "RealEstateAgency.h"

class Ui {
private:
    RealEstateAgency agency_list;
public:
    Ui(RealEstateAgency agency_list);
    //~Ui();
    void Start();
};
