#pragma once

#include <string>

class Domain {
private:
    std::string nationality, name, team;
    int goals;
public:
    Domain();
    Domain(std::string name, std::string nationality, std::string team, int goals);
    std::string getNationality();
    std::string  getName();
    std::string  getTeam();
    int getGoals();
};


