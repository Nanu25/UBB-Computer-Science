
#ifndef TESTPROFA_ISSUE_H
#define TESTPROFA_ISSUE_H


#include <string>

class Issue {
private:
    std::string description, status, reporter, solver;
public:
    Issue(std::string desc, std::string  status, std::string report, std::string solver);
    std::string  getDescription();
    std::string  getStatus();
    std::string  getReporter();
    std::string  getSolver();
    std::string  toString();

    void setSolver(std::string solver);
    void setStatus(std::string status);
};


#endif //TESTPROFA_ISSUE_H
