#include "MedicalAnalysis.h"

MedicalAnalysis::MedicalAnalysis(std::string date) {
    this->date = date;
}

bool MedicalAnalysis::isResultOK() {
    return false;
}

std::string MedicalAnalysis::toString() {
    return std::string();
}

std::string MedicalAnalysis::getDate() {
    return this->date;
}
