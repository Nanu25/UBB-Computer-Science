#pragma once

#include <string>
#include <vector>
#include "MedicalAnalysis.h"

class Person {
private:
    std::string name;
    std::vector <MedicalAnalysis*> repo;
public:
    Person();
    Person(std::string name);
    void addAnalysis(MedicalAnalysis* med);
    std::vector <MedicalAnalysis*> getAllAnalysis();
    std::vector <MedicalAnalysis*> getAnalysisMonth(int month);
    std::vector <MedicalAnalysis*> getAnalysisDate(std::string s1, std::string s2);
    void writeToFile(std::string filename, std::string s1, std::string s2);
    bool isIll(int month);
};
