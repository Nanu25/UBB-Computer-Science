
#include <fstream>
#include <algorithm>
#include "Repository.h"


Repository::Repository() {
}

void Repository::AddDevelopment(Development dev) {
    this->devo_repo.push_back(dev);
}

void Repository::AddIssue(Issue issue) {
    for (auto e : this->issue_repo) {
        if (e.getDescription() == issue.getDescription()) {
            throw std::runtime_error("This issue already exists");
        }
    }
    this->issue_repo.push_back(issue);

}

std::vector<Development> Repository::getDevoRepo() {
    return this->devo_repo;
}

bool cmp(Issue i1, Issue i2) {
    return i1.getStatus()  < i2.getStatus() || (i1.getStatus() == i2.getStatus() && i1.getDescription() < i2.getDescription());
}

std::vector<Issue>& Repository::getIssueRepo() {
    std::sort(this->issue_repo.begin(), this->issue_repo.end(), cmp);
    return this->issue_repo;
}

void Repository::readFile() {
    std::ifstream fin("../dev.txt");
    std::string name, type;
    while(fin >> name >> type) {
        this->AddDevelopment(Development{name, type});
    }
    fin.close();

    std::ifstream f("../issue.txt");
    std::string description, status, reporter, solver, line;
    while(std::getline(f, line)) {
        description="";
        int index = 0;
        while(line[index] != ',')
            description += line[index++];
        index++;

        status = "";
        while(line[index] != ',')
            status += line[index++];
        index++;

        reporter = "";
        while(line[index] != ',')
            reporter += line[index++];
        index++;

        solver="";
        while(index < line.size())
            solver += line[index++];

        this->AddIssue(Issue{description, status, reporter, solver});
    }
    f.close();
}

void Repository::removeIssue(std::string desc) {
    for (auto it = this->issue_repo.begin(); it != this->issue_repo.end(); ++it) {
        if (it->getDescription() == desc && it->getStatus() == "closed") {
            this->issue_repo.erase(it);
            return; // Exit the function after removing the issue
        }
    }
    throw std::runtime_error("Issue not ok to be removed");
}

void Repository::writeFile() {
//    std::ofstream fout("../issue.txt");
//    for(auto e : this->issue_repo) {
//        fout << e.getDescription() << "," << e.getStatus() << "," << e.getReporter() << "," << e.getSolver() << '\n';
//    }
//    fout.close();
}
