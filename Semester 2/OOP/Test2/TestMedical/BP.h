#pragma once

#include <string>
#include "MedicalAnalysis.h"

class BP : public MedicalAnalysis {
private:
    int systolicValue, diastolicValue;
public:
    BP(std::string date, int sys, int dia);
    bool isResultOK() override;
    std::string toString() override;
};