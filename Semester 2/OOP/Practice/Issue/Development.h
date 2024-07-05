
#ifndef TESTPROFA_DEVELOPMENT_H
#define TESTPROFA_DEVELOPMENT_H


#include <string>

class Development {
private:
    std::string name, type;
public:
    Development(std::string name, std::string type);
    std::string getName();
    std::string getType();

};


#endif //TESTPROFA_DEVELOPMENT_H
