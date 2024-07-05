//
// Created by alex_ on 6/27/2024.
//

#include <fstream>
#include "Repository.h"

std::vector<Researcher> &Repository::getResRepo() {
    return this->res_repo;
}

std::vector<Ideea> &Repository::getIdeeaRepo() {
    return this->ideea_repo;
}

void Repository::addIdeea(Ideea i1) {
    this->ideea_repo.push_back(i1);
}

void Repository::addResearcher(Researcher r) {
    this->res_repo.push_back(r);
}


void Repository::readFile() {
    std::ifstream fin("../researcher.txt");
    std::string name, position, line;
    while(std::getline(fin, line)) {
        int index = 0;
        name = "";
        while(line[index] != ',')
            name += line[index++];
        index++;

        position = "";
        while(index < line.size())
            position += line[index++];

        this->res_repo.push_back(Researcher{name, position});
    }
    fin.close();

    std::ifstream f("../ideea.txt");
     line;
    while(std::getline(f, line)) {
        std::string title = "";
        int index = 0;

        while(line[index] != ',')
            title += line[index++];
        index++;

        std::string description = "";
        while(line[index] != ',')
            description += line[index++];
        index++;

        std::string status = "";
        while(line[index] != ',')
            status += line[index++];
        index++;

        std::string creator = "";
        while(line[index] != ',')
            creator += line[index++];
        index++;

        int year = 0;
        while(index < line.size())
            year = line[index++] - '0';

        this->ideea_repo.push_back(Ideea{title, description, status, creator, year});
    }
    f.close();
}
