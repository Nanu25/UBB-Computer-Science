//
// Created by alex_ on 5/28/2024.
//

#include "Service.h"

Service::Service(Repository &repo) : serv_list(repo){

}

void Service::AddEquation(Equation e1) {
    this->serv_list.add(e1);
}

Repository &Service::getList() {
    return this->serv_list;
}

std::vector<std::complex<double>> Service::solve(int index) {
    std::vector<std::complex<double>> roots;
    Equation e = this->serv_list.getRepo()[index];
    double a = e.getA();
    double b = e.getB();
    double c = e.getC();
    if (a == 0) {
        if (b != 0)
            roots.push_back(-c / b);
    } else {
        double discriminant = e.getDiscriminant();
        std::complex<double> sqrtDiscriminant = std::sqrt(std::complex<double>(discriminant, 0));

        std::complex<double> root1 = (-b + sqrtDiscriminant) / (2.0 * a);
        std::complex<double> root2 = (-b - sqrtDiscriminant) / (2.0 * a);

        roots.push_back(root1);
        roots.push_back(root2);
    }

    return roots;
}