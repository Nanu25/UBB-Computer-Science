
#ifndef BILLS_BILLS_H
#define BILLS_BILLS_H


#include <string>

class Bills {
private:
    std::string name, code, paid;
    float cost;
public:
    Bills();
    Bills(std::string name, std::string code, float cost, std::string paid);
    float getCost();
    std::string getName();
    std::string toStr();
    std::string getPaid();


};


#endif //BILLS_BILLS_H
