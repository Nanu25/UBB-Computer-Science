#pragma once

#include <string>

class Building {
protected:
    int constructionYear;
public:
    Building(int year);
    virtual bool mustBeRestored();
    virtual bool canBeDemolished();
    virtual std::string toString();
    int getYear();
};


