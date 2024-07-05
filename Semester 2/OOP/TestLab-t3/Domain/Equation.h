
#ifndef TESTLAB_T3_EQUATION_H
#define TESTLAB_T3_EQUATION_H


#include <string>

class Equation {
private:
    double a, b, c;
public:
    Equation();
    Equation(double a, double b, double c);
    std::string toStr();
    double getDiscriminant();

    double getA();
    double getB();
    double getC();
};


#endif //TESTLAB_T3_EQUATION_H
