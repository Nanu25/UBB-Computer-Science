#pragma once

#include <vector>
#include "HospitalDepartment.h"

class Service {
private:
    std::vector <HospitalDepartment*> repo;
    std::vector <HospitalDepartment*> SortAllDepartment();
public:
    Service();
    void addDepartment(HospitalDepartment* x);
    std::vector <HospitalDepartment*> getAllDepartment();
    std::vector <HospitalDepartment*> getAllEfficientDepartments();
    void writeToFile(std::string filename);

};


