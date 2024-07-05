//
// Created by alex_ on 5/28/2024.
//

#include <sstream>
#include "Equation.h"

Equation::Equation() {

}

Equation::Equation(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

std::string Equation::toStr() {
    std::ostringstream oss;

    if (this->a != 0) {
        if(this->a != 1)
            oss << this->a << "x^2";
        else oss<< "x^2";
    }

    if (this->b != 0) {
        if (this->a != 0) {
            oss << (this->b > 0 ? " + " : " - ");
        } else if (this->b < 0) {
            oss << "-";
        }
        oss << std::abs(this->b) << "x";
    }

    if (this->c != 0) {
        if (this->a != 0 || this->b != 0) {
            oss << (this->c > 0 ? " + " : " - ");
        } else if (this->c < 0) {
            oss << "-";
        }
        oss << std::abs(this->c);
    }

    if (this->a == 0 && this->b == 0 && this->c == 0) {
        return "0";
    }

    return oss.str();

}

double Equation::getDiscriminant() {
    return b*b - 4*a*c;
}

double Equation::getA() {
    return this->a;
}

double Equation::getB() {
    return this->b;
}

double Equation::getC() {
    return this->c;
}
