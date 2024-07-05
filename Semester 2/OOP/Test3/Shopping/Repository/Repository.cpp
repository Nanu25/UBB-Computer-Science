
#include <fstream>
#include <sstream>
#include <iostream>
#include "Repository.h"


Repository::Repository() {

}

std::vector<Product> Repository::getRepo() {
    return this->repo;
}

void Repository::add(Product p) {
    this->repo.push_back(p);
}

void Repository::load_file(std::string filename) {
    std::ifstream f(filename);
    std::string s;
    while(std::getline(f, s)) {
        int i = 0;
        std::string category;
        while(s[i] != '|')
            category += s[i++];
        i++;
        category.pop_back();
        std::string name;
        while(s[i] != '|')
            name += s[i++];
        i++;
        name.pop_back();
        int quantity = 0;
        while(i < s.size()) {
            if (s[i] <= '9' && s[i] >= '0')
                quantity = quantity * 10 + (s[i] - '0');
            i++;
        }
        this->repo.push_back(Product{category, name, quantity});
    }

    f.close();
}

