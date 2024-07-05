#pragma once

#include "MedicalAnalysis.h"

class BMI : public MedicalAnalysis {
private:
    double value;
public:
    BMI(std::string name, double value);
    bool isResultOK() override;
    std::string toString() override;
};


