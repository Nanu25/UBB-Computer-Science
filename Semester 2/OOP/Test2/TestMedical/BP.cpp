#include "BP.h"

BP::BP(std::string date, int sys, int dia) : MedicalAnalysis(date) {
    this->systolicValue = sys;
    this->diastolicValue = dia;
}

bool BP::isResultOK() {
    if(this->systolicValue >= 90 && this->systolicValue <= 119 && this->diastolicValue >= 60 && this->diastolicValue <= 79)
        return 1;
    return 0;
}

std::string BP::toString() {
    std::string s = "Date: " + this->date + " systolic value: " + std::to_string(this->systolicValue) + " diastolic Value: " + std::to_string(this->diastolicValue);
    return s;
}
