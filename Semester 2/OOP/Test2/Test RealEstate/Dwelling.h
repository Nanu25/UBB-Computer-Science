#pragma once
class Dwelling {
private:
    double price;
    bool isProfitable;
public:
    Dwelling(double price, bool isProfitable);
    double getPrice();
    bool getProfitable();
};
