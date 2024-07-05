
#ifndef OOP_E_912_914_NANU25_RESEARCHER_H
#define OOP_E_912_914_NANU25_RESEARCHER_H


#include <string>

class Researcher {
private:
    std::string name, position;
public:
    Researcher(std::string name, std::string position);
    std::string getName();
    std::string getPosition();
};


#endif //OOP_E_912_914_NANU25_RESEARCHER_H
