#pragma once

#include "HospitalDepartment.h"

class NeonatalUnit : public HospitalDepartment {
private:
    int numberOfMothers, numberOfNewborns;
public:
    double agrageGrade;
    NeonatalUnit(std::string name, int nrd, int nrm, int nrb, double avg);

    bool isEfficient() override;
    std::string toString() override;
};


