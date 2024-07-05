
#ifndef DELIVERNOW_COURIER_H
#define DELIVERNOW_COURIER_H


#include <vector>
#include <string>

class Courier {
private:
    std::string name;
    std::vector <std::string> streets;
    int x, y, r;

public:
    Courier(std::string name, std::vector<std::string> streets,  int x, int y, int z);
    std::string getName();
    std::vector<std::string > getStreets();
    int getX();
    int getY();
    int getR();
};


#endif //DELIVERNOW_COURIER_H
