
#include "Package.h"

Package::Package(std::string recipient, std::string street, int locX, int locY, bool delivered) {
    this->recipient = recipient;
    this->street = street;
    this->locX = locX;
    this->locY = locY;
    this->delivered = delivered;
}

std::string Package::getRecipient() {
    return this->recipient;
}

std::string Package::getStreet() {
    return  this->street;
}

int Package::getLocX() {
    return this->locX;
}

int Package::getLocY() {
    return this->locY;
}

bool Package::getDelivery() {
    return this->delivered;
}

void Package::setDelivery() {
    this->delivered = 1;
}
