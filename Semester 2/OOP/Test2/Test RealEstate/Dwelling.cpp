#include "Dwelling.h"

double Dwelling::getPrice() {
    return this->price;
}

bool Dwelling::getProfitable() {
    return this->isProfitable;
}

Dwelling::Dwelling(double price, bool isProfitable) {
    this->price = price;
    this->isProfitable = isProfitable;
}

