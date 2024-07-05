
#include "Building.h"

Building::Building(int year) {
    this->constructionYear = year;
}

bool Building::mustBeRestored() {
    return false;
}

bool Building::canBeDemolished() {
    return false;
}

std::string Building::toString() {
    return "";
}

int Building::getYear() {
    return this->constructionYear;
}
