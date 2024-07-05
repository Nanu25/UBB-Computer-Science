
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Repository.h"

std::vector<Courier> &Repository::getCourrierRepo() {
    return this->courier_repo;
}

std::vector<Package> &Repository::getPackageRepo() {
    return this->package_repo;
}

void Repository::addCourier(Courier c) {
    this->courier_repo.push_back(c);
}

void Repository::addPackage(Package p) {
    this->package_repo.push_back(p);
}

void Repository::readFile() {
    std::ifstream f("../courier.txt");
    std::string line;
    while(std::getline(f, line)) {
        int index = 0;
        std::string name = "";
        while(line[index] != ',')
            name += line[index++];
        index++;

        std::vector <std::string> str;
        while(line[index] != ',') {
            std::string aux = "";
            while(line[index] != ';')
                aux += line[index++];
            index++;
            str.push_back(aux);
        }
        index++;
        int x = 0;
        while(line[index] != ',')
            x = x * 10 + line[index++] - '0';
        index++;

        int y = 0;
        while(line[index] != ',')
            y = y * 10 + line[index++] - '0';
        index++;

        int r = 0;
        while(index < line.size())
            r = r * 10 + line[index++] - '0';
        index++;

        this->courier_repo.push_back(Courier{name, str, x, y,r});
    }

    std::ifstream fin("../package.txt");
    while(std::getline(fin, line)) {
        std::string recipient = "";
        int index = 0;
        while(line[index] != ',')
            recipient += line[index++];
        index++;

        std::string street;
        while(line[index] != ',')
            street += line[index++];
        index++;

        int x = 0;
        while(line[index] != ',')
            x = x * 10 + line[index++] - '0';
        index++;

        int y = 0;
        while(line[index] != ',')
            y = y * 10 + line[index++] - '0';
        index++;

        bool delivered = line[index] - '0';
        this->package_repo.push_back(Package{recipient, street, x, y, delivered});
    }
}

std::vector<std::string> Repository::getStreets() {
    std::unordered_map <std::string, int> M;
    std::vector<std::string> aux;
    for(auto e : this->courier_repo) {
        for(auto it : e.getStreets()) {
            if(M[it] == 0) {
                M[it] = 1;
                aux.push_back(it);
            }
        }
    }
    return aux;
}
