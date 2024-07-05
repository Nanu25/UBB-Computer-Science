
#include <fstream>
#include <sstream>
#include "Repository.h"

std::vector<Equation> Repository::getRepo() {
    return this->repo;
}

void Repository::add(Equation e1) {
    this->repo.push_back(e1);
}

void Repository::load_file(std::string filename) {
    std::ifstream f(filename);
    std::string line;
    while (std::getline(f, line)) {
        std::istringstream iss(line);
        double a, b, c;
        char comma1, comma2;

        iss >> a >> comma1 >> b >> comma2 >> c;
        Equation e1(a, b, c);
        this->repo.push_back(e1);
    }

    f.close();
}
