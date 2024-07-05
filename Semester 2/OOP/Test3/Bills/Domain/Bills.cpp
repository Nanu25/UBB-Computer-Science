
#include "Bills.h"

Bills::Bills() {

}

Bills::Bills(std::string name, std::string code, float cost, std::string paid) {
    this->name = name;
    this->code = code;
    this->cost = cost;
    this->paid = paid;
}

float Bills::getCost() {
    return this->cost;
}

std::string Bills::getName() {
    return this->name;
}

std::string Bills::toStr() {
    return this->name + " - " + std::to_string(this->cost);
}

std::string Bills::getPaid() {
    return this->paid;
}
