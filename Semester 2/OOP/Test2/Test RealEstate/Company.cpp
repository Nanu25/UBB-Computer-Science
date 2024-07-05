#include "Company.h"

double Company::totalIncome() {
    return this->moneyFromInvestments + this->income;
}

std::string Company::toString() {
    std::string s = "Name: " + this->name + " income: " + std::to_string(this->income) + " money from investments: " + std::to_string(this->moneyFromInvestments);
    return s;

}

bool Company::isInterested(Dwelling x) {
    return (x.getPrice() / 100 <= this->income && x.getProfitable() == 1);
}

Company::Company(std::string name, double income, double moneyInvestments) : Client(name, income) {
    this->moneyFromInvestments = moneyInvestments;
}

//Company::~Company() {
//
//}
