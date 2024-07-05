#include "Client.h"

Client::Client(std::string name, double income) {
    this->name = name;
    this->income = income;
}

double Client::totalIncome() {
    return this->income;
}

bool Client::isInterested(Dwelling x) {
    return x.getProfitable();
}

std::string Client::getName() {
    return this->name;
}

std::string Client::toString() {
    std::string s = "Name: " + this->name + " income: " + std::to_string(this->income);
    return s;
}

//Client::Client() {
//
//}
//
