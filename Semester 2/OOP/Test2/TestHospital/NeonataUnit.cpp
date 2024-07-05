
#include "NeonataUnit.h"

NeonatalUnit::NeonatalUnit(std::string name, int nrd, int nrm, int nrb, double avg) : HospitalDepartment(name, nrd) {
    this->numberOfMothers = nrm;
    this->numberOfNewborns = nrb;
    this->agrageGrade = avg;
}

bool NeonatalUnit::isEfficient() {
    return (this->agrageGrade > 8.5 && this->numberOfNewborns >= this->numberOfMothers);
}

std::string NeonatalUnit::toString() {
    std::string s = " Hospital name: " + this->hospitalName + " number of Doctors: " + std::to_string(this->numberOfDoctors) + " number of mothers: " + std::to_string(this->numberOfMothers) + " number of newborns " + std::to_string(this->numberOfNewborns) + " avrage grade: " + std::to_string(this->agrageGrade) + " is efficient: " + std::to_string(this->isEfficient());
    return s;
}
