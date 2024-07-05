#pragma once

#include <string>

class HospitalDepartment {
protected:
    std::string hospitalName;
    int numberOfDoctors;
public:
    HospitalDepartment(std::string name, int nr);
    virtual bool isEfficient();
    virtual std::string toString();
    std::string getName();

};


