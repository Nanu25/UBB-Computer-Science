
#ifndef TESTLAB_T3_REPOSITORY_H
#define TESTLAB_T3_REPOSITORY_H


#include <vector>
#include "../Domain/Equation.h"

class Repository {
private:
    std::vector <Equation> repo;
public:
    std::vector <Equation> getRepo();
    void add(Equation e1);
    void load_file(std::string filename);
};


#endif //TESTLAB_T3_REPOSITORY_H
