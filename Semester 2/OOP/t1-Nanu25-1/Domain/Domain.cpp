#include "Domain.h"

Domain::Domain() {

}

Domain::Domain(std::string name, std::string nationality, std::string team, int goals) {
    this->nationality = nationality;
    this->name = name;
    this->team = team;
    this->goals = goals;
}

std::string Domain::getNationality() {
    return this->nationality;
}

std::string Domain::getName() {
    return this->name;
}

std::string Domain::getTeam() {
    return this->team;
}

int Domain::getGoals() {
    return this->goals;
}


