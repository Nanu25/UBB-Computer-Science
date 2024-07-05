#pragma once

#include "Building.h"

class House : public Building{
private:
    bool isHistorical;
public:
    House(int year, bool ok);
    bool mustBeRestored() override;
    bool canBeDemolished() override;
    std::string toString() override;
};


