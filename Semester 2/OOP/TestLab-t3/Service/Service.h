
#ifndef TESTLAB_T3_SERVICE_H
#define TESTLAB_T3_SERVICE_H


#include <complex>
#include "../Repository/Repository.h"

class Service {
private:
    Repository& serv_list;
public:
    Service(Repository& repo);
    void AddEquation(Equation e1);
    Repository& getList();

    std::vector<std::complex<double>> solve(int index);
};


#endif //TESTLAB_T3_SERVICE_H
