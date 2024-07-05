
#include <fstream>
#include <iostream>
#include "Repository.h"

std::vector<Bills> Repository::getRepo() {
    return this->repo;
}

void Repository::load_file(std::string filename) {
    std::ifstream f(filename);
    std::string s;
    while(std::getline(f, s)) {
        int i = 0;
        std::string name;
        while(s[i] != ';')
            name += s[i++];
        i++;
        i++;

        std::string code;
        while(s[i] != ';')
            code += s[i++];
        i++;
        i++;

        //this is a float number in a string and i want to convert it to float
        std::string number;
        while(s[i] != ';')
            number += s[i++];
        i++;
        i++;
        float num = std::stof(number);

        std::string paid;
        while(i < s.size())
            paid += s[i++];

        std::cout << number << " ";
        repo.push_back(Bills(name, code, num, paid));
    }

}
