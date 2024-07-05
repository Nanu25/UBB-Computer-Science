#pragma once

#include "Building.h"

class Block : public Building {
private:
    int totalApartments;
    int occupiedAppartament;
public:
    Block(int year, int totap, int ocap);
    bool mustBeRestored() override;
    bool canBeDemolished() override;
    std::string toString() override;
};


