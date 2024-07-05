#pragma once

#include "Client.h"

class Company: public Client{
private:
    double moneyFromInvestments;
public:
    Company(std::string name, double income, double moneyInvestments);
    double totalIncome() override;
    std::string toString() override;
    bool isInterested(Dwelling x) override;
};


