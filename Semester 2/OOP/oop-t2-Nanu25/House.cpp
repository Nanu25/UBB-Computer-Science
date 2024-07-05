
#include "House.h"

House::House(int year, bool ok) : Building(year) {
    this->isHistorical = ok;
}

bool House::mustBeRestored() {
    return 2024 - this->constructionYear > 100;
}

bool House::canBeDemolished() {
    return !this->isHistorical;
}

std::string House::toString() {
    std::string s = "House Building Construction year " + std::to_string(this->constructionYear) + " is historical " + std::to_string(this->isHistorical);
    return s;
}
