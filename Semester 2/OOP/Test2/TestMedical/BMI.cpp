#include "BMI.h"

BMI::BMI(std::string name, double value) : MedicalAnalysis(name) {
    this->value = value;
}

bool BMI::isResultOK() {
    if(this->value >= 18.5 && this->value <= 25)
        return 1;
    return 0;
}

std::string BMI::toString() {
    std::string s = "Date: " + this->date + " BMI value: " + std::to_string(this->value);
    return s;
}
