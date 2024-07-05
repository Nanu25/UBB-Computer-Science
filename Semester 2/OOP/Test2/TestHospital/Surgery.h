#pragma once

#include "HospitalDepartment.h"

class Surgery : public HospitalDepartment {
private:
    int numberOfPatients;
public:
    Surgery(std::string name, int nrd, int nrp);
    bool isEfficient() override;
    std::string toString() override;
};


