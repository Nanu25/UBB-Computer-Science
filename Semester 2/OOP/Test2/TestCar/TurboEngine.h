#include "Engine.h"

class TurboEngine : public Engine{
public:
    TurboEngine(std::string fuel);
    double getPrice() override;
    std::string toString() override;

};


