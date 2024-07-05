#pragma once

#include <vector>
#include "../Domain/Task.h"

class Repository {
private:
    std::vector <Task> repo;
public:
    Repository();
    std::vector <Task> getRepo();
    void add(Task t);
    void load_file(std::string filename);
};


