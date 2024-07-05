#pragma once

#include <string>

class MedicalAnalysis {
protected:
    std::string date;

public:
    MedicalAnalysis(std::string date);
    virtual bool isResultOK();
    virtual std::string toString();
    std::string getDate();
};


