
#include "Courier.h"

Courier::Courier(std::string name, std::vector<std::string> streets,  int x, int y, int z) {
    this->name = name;
    this->x = x;
    this->y = y;
    this->r = z;
    for(auto e : streets)
        this->streets.push_back(e);
}

std::string Courier::getName() {
    return this->name;
}

std::vector<std::string> Courier::getStreets() {
    return this->streets;
}

int Courier::getX() {
    return this->x;
}

int Courier::getY() {
    return this->y;
}

int Courier::getR() {
    return this->r;
}

