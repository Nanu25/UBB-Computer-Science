
#include "Surgery.h"

Surgery::Surgery(std::string name, int nrd, int nrp) : HospitalDepartment(name, nrd) {
    this->numberOfPatients = nrp;
}

bool Surgery::isEfficient() {
    double x = (double)this->numberOfPatients / this->numberOfDoctors;
    return (x >= 2);
}

std::string Surgery::toString() {
    std::string s = " Hospital name: " + this->hospitalName + " number of Doctors: " + std::to_string(this->numberOfDoctors) + " number of patients: " + std::to_string(this->numberOfPatients) + " is efficient: " + std::to_string(this->isEfficient());
    return s;
}
