#include <string>
#include "Engine.h"

#include "ElectricEngine.h"
#include "TurboEngine.h"

class Car {
private:
    std::string bodyStyle;
    Engine* eng;
public:
    Car(std::string bodyStyle, std::string engineType, std::string fuelType, int autonomy);
    double computePrice();
    std::string toString();
};


