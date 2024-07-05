#include "HospitalDepartment.h"

HospitalDepartment::HospitalDepartment(std::string name, int nr) {
    this->hospitalName = name;
    this->numberOfDoctors = nr;
}

bool HospitalDepartment::isEfficient() {
    return false;
}

std::string HospitalDepartment::toString() {
    return std::string();
}

std::string HospitalDepartment::getName() {
    return this->hospitalName;
}
