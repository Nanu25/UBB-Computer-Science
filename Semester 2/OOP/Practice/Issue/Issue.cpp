
#include "Issue.h"


Issue::Issue(std::string desc, std::string status, std::string report, std::string solver) {
    this->description = desc;
    this->status = status;
    this->reporter = report;
    this->solver = solver;
}

std::string Issue::getDescription() {
    return this->description;
}

std::string Issue::getStatus() {
    return this->status;
}

std::string Issue::getReporter() {
    return this->reporter;
}

std::string Issue::getSolver() {
    return this->solver;
}

std::string Issue::toString() {
    return this->getDescription() + " " + this->getStatus() + " " + this->getReporter() + " " + this->getSolver();
}

void Issue::setSolver(std::string solver) {
    this->solver = solver;
}

void Issue::setStatus(std::string status) {
    this->status = status;
}
