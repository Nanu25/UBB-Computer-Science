
#include <fstream>
#include <sstream>
#include "Repository.h"

Repository::Repository() {

}

std::vector<Task> Repository::getRepo() {
    return this->repo;
}

void Repository::add(Task t) {
    this->repo.push_back(t);
}

void Repository::load_file(std::string filename) {
    std::ifstream f(filename);
    std::string s;
    while(std::getline(f, s)) {
        std::istringstream iss(s);
        std::string task;
        int duration, priority;
        char sep;
        iss >> task >> sep >> duration  >> sep >> priority;
        this->repo.push_back(Task(task, duration, priority));
    }
}
